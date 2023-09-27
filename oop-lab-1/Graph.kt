import java.lang.IllegalArgumentException

open class Graph<T> {
    protected data class Vertex<T>(val name: T) {
        val neighbors = mutableMapOf<Vertex<T>, Int>()
    }

    private val vertices = mutableMapOf<T, Vertex<T>>()

    fun addVertex(name: T) {

        vertices[name] = Vertex(name)

    }

    fun connectVertex(first: T, second: T, weight: Int) { //connecting two vertices with checking if they are contained in vertices map
        if (vertices.containsKey(first) && vertices.containsKey(second)) {
            val startV = vertices[first]
            val destV = vertices[second]
            startV!!.neighbors[destV!!] = weight
            destV.neighbors[startV] = weight //for some reason only destV need to be asserted as non-nullable
        } else {
            throw IllegalArgumentException()
        }
    }

    private fun getNeighborMap(name: T): Map<T, Int> { // for singular vertex we get a map of all neighbours with edge's weight
        val vertex = vertices[name]
        if (vertex != null) {
            val neighborMap = mutableMapOf<T, Int>()
            val neighbors = vertex.neighbors
            for ((neighbor, weight) in neighbors) {
                neighborMap[neighbor.name] = weight
            }
            return neighborMap


        } else
            return mutableMapOf()

    }

    fun findMinSpanTreePrim(): MinimumSpanningTree<T> { //finding of a minimal spanning tree using Prim's algorithm.
        val visited = mutableSetOf<T>()                 // i also plan on adding Kruskal's algorithm
        val minimumSpanningTree = MinimumSpanningTree<T>()
        if (vertices.isEmpty()) {
            return minimumSpanningTree
        }
        val startVertex = vertices.values.first()
        visited.add(startVertex.name)

        while (visited.size < vertices.size) {
            var minWeight = Int.MAX_VALUE
            var nextVertex: T? = null
            var currVertex: T? = null

            for (vertexName in visited) {
                val vertex = vertices[vertexName] ?: continue

                for ((neighbor, weight) in vertex.neighbors) {
                    if (neighbor.name !in visited && weight < minWeight) {
                        minWeight = weight
                        nextVertex = neighbor.name
                        currVertex = vertex.name
                    }
                }
            }
            if (nextVertex != null && currVertex != null) {
                visited.add(nextVertex)
                minimumSpanningTree.addEdge(currVertex, nextVertex, minWeight)
            } else {
                break
            }

        }
        return minimumSpanningTree
    }


    fun findMinSpanTreeKruskal(): MinimumSpanningTree<T> { //works not as intended; edges display two times (for example, 1--3 and 3--1)
        val minimumSpanningTree = MinimumSpanningTree<T>()
        if (vertices.isEmpty()) {
            return minimumSpanningTree
        }
        val allEdges = mutableListOf<Pair<Pair<T, T>, Int>>() // edge consists of a pair of vertices and its weight
        for ((name1, vertex1) in vertices) {
            for ((vertex2, weight) in vertex1.neighbors) {
                val edge = Pair(Pair(name1, vertex2.name), weight)
                allEdges.add(edge)
            }
        }

        val sortedEdges = allEdges.sortedBy { it.second } //sorting all edges by their weight

        val unionFind = UnionFind<T>()
        for (name in vertices.keys) {
            unionFind.makeComponent(name)
        }

        for((edge, weight) in sortedEdges) {
            val (vertex1, vertex2) = edge
            if (!unionFind.inSameComponent(vertex1, vertex2)) {
                minimumSpanningTree.addEdge(vertex1, vertex2, weight)
                unionFind.union(vertex1, vertex2)
            }
        }


        return minimumSpanningTree

    }


        fun showNeighbors(name: T) {

            for ((neighbor, weight) in getNeighborMap(name)) {
                println("neighbor: $neighbor, weight: $weight\n")
            }


        }


        private operator fun get(name: T): Vertex<T> { //operator override function used for getting Vertex objects from their names
            return vertices[name] ?: throw IllegalArgumentException()
        }
    }



