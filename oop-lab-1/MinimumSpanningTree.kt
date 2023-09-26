class MinimumSpanningTree<T> {
    private val edges = mutableListOf<Pair<T,T>>()
    private val weights = mutableListOf<Int>()

    fun addEdge(nameVert1: T, nameVert2: T, weight: Int) {
        edges.add(Pair(nameVert1, nameVert2))
        weights.add(weight)
    }

    fun printMinSpanTree() {
        println("minimum spanning tree contains of:")
        for (i in edges.indices) {
            val (vertex1, vertex2) = edges[i]
            val weight2 = weights[i]
            println("edge: $vertex1 -- $vertex2  (weight = $weight2)")
        }
    }
}