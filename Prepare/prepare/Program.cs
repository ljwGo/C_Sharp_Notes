using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text.Json;
using System.Threading;


namespace prepare {

    // 构建简单的多枝树(取材自饥荒)
    public class Employee {
        public string id;
        public string name;
    }

    public class Link {
        public string fromId;
        public string toId;

        public Link(string fromId, string toId) {
            this.fromId = fromId;
            this.toId = toId;
        }
    }

    // 迭代器模式相关接口
    public interface Iterator<Ele> {
        public bool MoveNext();
        public Ele Current { get; }
        public void Reset();
    }

    public interface Iterable<Ele> {
        public Iterator<Ele> iterator();
    }

    public interface Collection<Ele, Link> : Iterable<Ele> {
        public void Add(Ele ele);
        public void Remove(string id);
        public void AddLink(string id, Link link);
        public void RemoveLink(string id);
        public void ReverseLink(string toId, string fromId);
    }

    public class MutipleTwigTree : Collection<Employee, Link> {
        // 内部类, 返回Iterator
        private class TempIterator : Iterator<Employee> {

            private MutipleTwigTree mutipleTwigTree;
            private int totalIndex = 0;
            List<Link> links;
            private string fromId;
            private string toId;
            private int cursorIdx;
            private bool isFirst = true;
            private Dictionary<string, int> keyMap = new Dictionary<string, int>();

            private TempIterator() {
                ;
            }

            public TempIterator(MutipleTwigTree tree) {
                mutipleTwigTree = tree;
                fromId = mutipleTwigTree.treeRootId;
                toId = mutipleTwigTree.treeRootId;
            }

            // 使用的是树结构的深层遍历(其它的包括前序遍历, 中序遍历和后序遍历)
            public Employee Current
            {
                get {
                    /* 所有目标更换, 只要找到一个还有子节点没被遍历的父节点即可 */

                    // 写得不好只能加个判断了
                    if (isFirst) {
                        isFirst = false;
                        totalIndex++;
                        return mutipleTwigTree.employeeMap[mutipleTwigTree.treeRootId];
                    }

                    // 获取fromId当前节点的Links列表(初始化)
                    links = null;
                    mutipleTwigTree.linkMap.TryGetValue(fromId, out links);

                    cursorIdx = 0;

                    // 确保当且节点以下有未遍历的节点
                    while (null == links || cursorIdx >= links.Count) {

                        // 返回上一节点
                        fromId = mutipleTwigTree.reverseLinkMap[fromId];
                        // 更新上一节点的links列表和cursorIdx
                        links = mutipleTwigTree.linkMap[fromId];
                        cursorIdx = GetCursorIdx(fromId);
                    }

                    toId = GetNextId(fromId, links);

                    // 记录子节点通往父节点
                    mutipleTwigTree.ReverseLink(toId, fromId);
                    // 同步移动到下一层
                    fromId = toId;

                    totalIndex++;
                    return mutipleTwigTree.employeeMap[fromId];
                }
            }

            public string GetNextId(string fromId, List<Link> links) {
                cursorIdx = GetCursorIdx(fromId);
                // 下一个节点的toId
                string toId = links[cursorIdx].toId;
                // 对应浮游标记自增1
                keyMap[fromId]++;
                // 获取下一个节点
                return toId;
            }

            public int GetCursorIdx(string fromId) {
                if (keyMap.ContainsKey(fromId)) {
                    cursorIdx = keyMap[fromId];
                }
                else {
                    // 存放新游标
                    cursorIdx = 0;
                    keyMap.Add(fromId, 0);
                }
                return cursorIdx;
            }

            public bool MoveNext() {
                return totalIndex < mutipleTwigTree.employeeMap.Count;
            }

            public void Reset() {
                totalIndex = 0;
            }
        }

        private string treeRootId;
        private string treeName;

        // 存放雇员节点
        private Dictionary<string, Employee> employeeMap = new Dictionary<string, Employee>();

        // 存放对应id节点下的所有链路
        private Dictionary<string, List<Link>> linkMap = new Dictionary<string, List<Link>>();

        // 从子节点返回父节点, 通过id标记
        private Dictionary<string, string> reverseLinkMap = new Dictionary<string, string>();

        public MutipleTwigTree(string treeRootId, string treeName) {
            this.treeName = treeName;
            this.treeRootId = treeRootId;
        }

        // C#字典不允许添加相同的键
        public void Add(Employee ele) {
            if (!employeeMap.ContainsKey(ele.id)) {
                employeeMap.Add(ele.id, ele);
            }
            else {
                throw new Exception("字典的键已经存在");
            }
        }

        public void AddLink(string id, Link link) {
            // 如果某节点下的链接列表已经存在
            if (linkMap.ContainsKey(id)) {
                linkMap[id].Add(link);
            }
            else {
                List<Link> links = new List<Link>();
                links.Add(link);
                linkMap.Add(id, links);
            }
        }

        // 一些需要遍历的场景下, 会默认调用该方法依次
        public Iterator<Employee> iterator() {
            // Java中允许这种类似匿名函数的"匿名类"
            // return new Iterator<Employee>{ 类体 };
            return new TempIterator(this);
        }

        public void Remove(string id) {
            if (employeeMap.ContainsKey(id)) {
                employeeMap.Remove(id);
            }
        }

        public void RemoveLink(string id) {
            if (linkMap.ContainsKey(id)) {
                linkMap.Remove(id);
            }
        }

        public void ReverseLink(string toId, string fromId) {
            if (!reverseLinkMap.ContainsKey(toId)) {
                // key: 子节点id; value: 父节点id
                reverseLinkMap.Add(toId, fromId);
            }
        }
    }

    class Program {
        static void Main(string[] args) {
 
        }
    }
}

