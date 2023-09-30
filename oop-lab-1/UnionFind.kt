class UnionFind<T> {

    //class used for Kruskal's algorithm. it is used on spanning trees.
    // in this class we form connectivity components, find which component does vertex belong to (findParent method) and can unite two components into one
    private val parent = mutableMapOf<T, T>()
    private val rank = mutableMapOf<T, Int>() // rank represents depth of the tree, used for uniting two trees so that resulting tree is more balanced

    fun makeComponent(element: T) {         //creating of new set that represents connectivity component
        parent[element] = element
        rank[element] = 0
    }

    //finding a "parent", meaning root element, gives us info about connectivity component.
    // if two vertices have same parent = they belong to the same component.
    fun findParent(element: T) : T {
        if (element != parent[element]) {
            parent[element] = findParent(parent[element]!!)
        }
        return parent[element]!!
    }

    fun inSameComponent(element1: T, element2:T) : Boolean {
        return findParent(element1) == findParent(element2)
    }
    //if we are uniting component A and component B, all we do is set root of A as a parent of a root of B
    //. since B has its own children, they all become children of A, meaning they are now on the same component
    fun union(element1:T, element2:T) {
        val rootEl1 = findParent(element1)
        val rootEl2 = findParent(element2)
        if (rootEl1 != rootEl2) {
            if (rank[rootEl1]!! < rank[rootEl2]!!) {
                parent[rootEl1] = rootEl2
            } else if (rank[rootEl2]!! < rank[rootEl1]!!) {
                parent[rootEl2] = rootEl1
            }
        }
        else {
            parent[rootEl2] = rootEl1
            rank[rootEl1] = rank[rootEl1]!! + 1
        }
    }
}