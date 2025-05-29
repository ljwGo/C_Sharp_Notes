using PoolManager.BaseInfo;
using PoolManager.BasePool;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;

namespace PoolManager.Core {
    public class PoolManager : MonoBehaviour {

        public static PoolManager Instance { get; private set; }
        public List<PoolConfig> poolConfigs = new List<PoolConfig>();
        public int maxPoolCount;

        private static Dictionary<string, UnityAction> allSleepHasSameTagHandlers = new Dictionary<string, UnityAction>();
        private static Dictionary<string, UnityAction> allActivateHasSameTagHandlers = new Dictionary<string, UnityAction>();
        private static Dictionary<string, ObjectPool> allPools = new Dictionary<string, ObjectPool>();

        private void Awake() {
            if (Instance != null) {
                Destroy(gameObject);
                return;
            }

            Instance = this;
            DontDestroyOnLoad(gameObject);
        }

        private void Start() {
            foreach (PoolConfig pool in poolConfigs) {
                pool.Init();
            }
            int sceneIndex = SceneManager.GetActiveScene().buildIndex;
            // 创建当前场景下所需的对象池
            InitPool(sceneIndex);

            // 更换场景时，加载正确的池子
            SceneManager.sceneLoaded += UpdatePool;
        }

        public static GameObject GetGo(GameObject go) {
            return GetPool(go).GetGo();
        }

        public static void SleepGo(GameObject go) {
            GetPool(go).SleepGo(go);
        }

        public static ObjectPool GetPool(GameObject go) {

            ObjectPool sp;
            string name = go.name;

            if (allPools.TryGetValue(name, out sp)) {
                return sp;
            }
            else if (name.EndsWith("(Clone)")) {
                allPools.TryGetValue(name.Substring(0, name.Length-7-1), out sp);
                return sp;
            }
            else {
                throw new KeyNotFoundException("SpawnPool which contain prefab with name \"" + name + "\" isn't exist!");
            }
        }

        public static void SetOnAllSleep(GameObject go, UnityAction <ObjectPool> handler) {
            ObjectPool op = GetPool(go);
            if (op.onAllSleep == null) {
                op.onAllSleep = handler;
            }
            else {
                op.onAllSleep += handler;
            }
        }

        public static void SetOnAllActivate(GameObject go, UnityAction<ObjectPool> handler) {
            ObjectPool op = GetPool(go);
            if (op.onAllActivate == null) {
                op.onAllActivate = handler;
            }
            else {
                op.onAllActivate += handler;
            }
        }

        public static void SetOnAllSleepHasSameTag(string tag, UnityAction handler) {
            if (allSleepHasSameTagHandlers.ContainsKey(tag)) {
                allSleepHasSameTagHandlers[tag] += handler;
            }
            else {
                allSleepHasSameTagHandlers.Add(tag, handler);
            }
        }
        
        public static void SetOnAllActivateHasSameTag(string tag, UnityAction handler) {
            if (allActivateHasSameTagHandlers.ContainsKey(tag)) {
                allActivateHasSameTagHandlers[tag] += handler;
            }
            else {
                allActivateHasSameTagHandlers.Add(tag, handler);
            }
        }

        private void InitPool(int sceneIndex) {
            ObjectPool newPool;

            foreach (PoolConfig info in poolConfigs) {
                // pool is not belong to current scene.
                if (info.buildSceneIndex != sceneIndex) {
                    continue;
                }

                // SpawnPool is already exist because of reloading scene. 
                if (allPools.ContainsKey(info.PoolName)) {
                    // SpawnPool's agentObj had been destoried
                    if (info.destoryOnReload) {
                        allPools[info.PoolName].Init();
                    }
                }
                // SpawnPool is not exist.
                else {
                    newPool = new ObjectPool(info);
                    newPool.onAllActivate = DetectAllActivateHasSameTag;
                    newPool.onAllSleep = DetectAllSleepHasSameTag;
                    allPools.Add(info.PoolName, newPool);
                }
            }
        }

        // 切换场景后
        private void UpdatePool(Scene scene, LoadSceneMode mode) {
            while (allPools.Count > maxPoolCount) {
                RemovePriorityLessPool();
            }
            InitPool(scene.buildIndex);
        }

        private void RemovePriorityLessPool() {
            allPools.Remove(GetPriorityLessPoolName());
        }

        private string GetPriorityLessPoolName() {
            string poolName = null;

            foreach (string name in allPools.Keys) {
                if (poolName == null) {
                    poolName = name;
                    continue;
                }

                if (allPools[name].poolConfig.priority >
                    allPools[poolName].poolConfig.priority) {
                    poolName = name;
                };
            }
            return poolName;
        }

        private void DetectAllSleepHasSameTag(ObjectPool op) {
            string tag = op.poolConfig.agentObject.tag;
            bool isFound = false;
            if (allSleepHasSameTagHandlers.ContainsKey(tag)) {
                foreach (ObjectPool pool in allPools.Values) {
                    if (pool.poolConfig.agentObject.tag == tag) {
                        isFound = true;

                        if (!pool.IsActivePoolEmpty()) { // 存在一个不为空
                            return;
                        }
                    }
                }

                if (isFound) { // 至少要有一个
                    allSleepHasSameTagHandlers[tag]?.Invoke();
                }
            }
        }

        private void DetectAllActivateHasSameTag(ObjectPool op) {
            bool isFound = false;

            if (allActivateHasSameTagHandlers.ContainsKey(tag)) {
                foreach (ObjectPool pool in allPools.Values) {
                    if (pool.poolConfig.agentObject.tag == tag) {
                        isFound = true;

                        if (!pool.IsSleepPoolEmpty()) {
                            return;
                        }
                    }
                }

                if (isFound) {
                    allActivateHasSameTagHandlers[tag]?.Invoke();
                }
            }
        }
    }
}
