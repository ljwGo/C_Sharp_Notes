using PoolManager.BasePool;
using UnityEngine;

public class PoolObject : MonoBehaviour, IPoolObject {
    public void OnActivate(ObjectPool po) {
        throw new System.NotImplementedException();
    }

    public void OnSleep(ObjectPool po) {
        throw new System.NotImplementedException();
    }
}
