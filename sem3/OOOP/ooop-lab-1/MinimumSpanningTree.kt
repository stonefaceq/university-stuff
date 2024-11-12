class MinimumSpanningTree<T> {                      //class used to create spanning trees objects when calling findMinSpanTreePrim(or Kruskal)
    private val edges = mutableListOf<Pair<T,T>>() //in Graph class
    private val weights = mutableListOf<Int>()      //minimum spanning tree is a tree that has no cycles, has all graph's vertices and has a minimum sum of all edge weights

    fun addEdge(nameVert1: T, nameVert2: T, weight: Int) { //also used in findMinSpanTreePrim()
        edges.add(Pair(nameVert1, nameVert2))
        weights.add(weight)
    }

    fun printMinSpanTree() {
        println("minimum spanning tree consists of:")
        for (i in edges.indices) {
            val (vertex1, vertex2) = edges[i]
            val weight2 = weights[i]
            println("edge: $vertex1 -- $vertex2  (weight = $weight2)")
        }
    }
}