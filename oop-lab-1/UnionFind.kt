class UnionFind<T> { //class used for Kruskal's algorithm
    private val parent = mutableMapOf<T, T>()
    private val rank = mutableMapOf<T, Int>() // rank represents depth of the tree, used for uniting two trees so that resulting tree is more balanced

    fun makeComponent(element: T) {         //creating of new set that represents connectivity component
        parent[element] = element
        rank[element] = 0
    }

    fun findParent(element: T) : T {
        if (element != parent[element]) {
            parent[element] = findParent(parent[element]!!)
        }
        return parent[element]!!
    }

    fun inSameComponent(element1: T, element2:T) : Boolean {
        return findParent(element1) == findParent(element2)
    }

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