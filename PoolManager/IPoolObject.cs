using PoolManager.BasePool;

public interface IPoolObject 
{
    void OnSleep(ObjectPool po);
    void OnActivate(ObjectPool po);
}
