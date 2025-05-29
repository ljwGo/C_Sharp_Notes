using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using PoolManager.BaseInfo;

namespace PoolManager.BasePool {
    public class ObjectPool{
        public PoolConfig poolConfig;
        public UnityAction<ObjectPool> onAllActivate;
        public UnityAction<ObjectPool> onAllSleep;

        private List<GameObject> activeGos = new List<GameObject>();
        private List<GameObject> sleepGos = new List<GameObject>();
        private int maxPoolSize;

        public ObjectPool(PoolConfig poolConfig) {
            this.poolConfig = poolConfig;
            maxPoolSize = 0;
        }

        public void Init() {
            sleepGos.Clear();
            activeGos.Clear();
            maxPoolSize = 0;
            CacheGos(poolConfig.agentObject, poolConfig.poolSize, poolConfig.destoryOnReload);
        }

        public GameObject GetGo() {
            GameObject newGo;

            if (sleepGos.Count > 0) {
                newGo = sleepGos[sleepGos.Count - 1];
                newGo.SetActive(true);

                PoolObject po = newGo.GetComponent<PoolObject>();
                if (po != null) {
                    po.OnActivate(this);
                }

                activeGos.Add(newGo);
                sleepGos.Remove(newGo);
                return newGo;
            }

            if (poolConfig.allowExtend) {
                // 如果扩展数不为0
                if (ExtendPoolSize(poolConfig.extendSizeOnce, maxPoolSize, poolConfig.maxPoolSize) != 0)
                    return GetGo();
            }

            if (IsSleepPoolEmpty()) {
                onAllActivate?.Invoke(this);
            }

            throw new System.Exception("休眠池已经没有对象可供使用；并且该对象池不允许扩展， 或者已经扩展到最大容量");
        }

        public void SleepGo(GameObject go) {
            go.SetActive(false);

            activeGos.Remove(go);
            sleepGos.Add(go);

            PoolObject po = go.GetComponent<PoolObject>();
            if (po != null) {
                po.OnSleep(this);
            }

            if (IsActivePoolEmpty()) {
                onAllSleep?.Invoke(this);
            }
        }

        public bool IsActivePoolEmpty() { 
            return activeGos.Count == 0;
        }
        
        public bool IsSleepPoolEmpty()
        {
            return sleepGos.Count == 0;
        }

        // 如果沉睡池中没有对象了, 那么他会准备好多个新的对象, 而非只调用一次instantiate; @return: 返回扩展大小
        private int ExtendPoolSize(int extendSize, int currentSize, int maxSize) {
            int actualExtendSize = Mathf.Min(extendSize, maxSize - currentSize);

            CacheGos(poolConfig.agentObject, actualExtendSize, poolConfig.allowExtend);
            return actualExtendSize;
        }
                
        private int CacheGos(GameObject go, int size, bool destoryOnLoad) {
            GameObject newGo;

            for (int i = 0; i < size; i++) {
                newGo = Object.Instantiate(go);
                if (!destoryOnLoad) {
                    MonoBehaviour.DontDestroyOnLoad(go);
                }

                newGo.SetActive(false);
                sleepGos.Add(newGo);
            }

            maxPoolSize += size;
            return size;
        }
    }
}
