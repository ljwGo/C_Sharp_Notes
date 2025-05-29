using UnityEngine;

namespace PoolManager.BaseInfo {
    [System.Serializable]
    public class PoolConfig {
        public int buildSceneIndex;  // 所属场景的索引
        public int poolSize;
        public int extendSizeOnce;
        public int maxPoolSize;
        public int priority;
        public bool destoryOnReload;
        public bool allowExtend;
        public GameObject agentObject;
        public string PoolName { get; private set; }

        public void Init() {
            PoolName = agentObject.name;
            priority = destoryOnReload ? 999 : priority;
        }
    }
}

