import java.lang.IllegalArgumentException

open class Graph<T> {
    //i didn't use class Edge here, instead i used mutable maps to save data about edges and their weight
    protected data class Vertex<T>(val name: T) {
        val neighbors = mutableMapOf<Vertex<T>, Int>() //used to save info about neighbors, as well as edge's weight
    }

    private val vertices = mutableMapOf<T, Vertex<T>>() //vertices are saved as maps containing their name T as keys and objects of class Vertex as values

    fun addVertex(name: T) {

        vertices[name] = Vertex(name)

    }

    fun connectVertex(first: T, second: T, weight: Int) { //connecting two vertices with checking if they are contained in vertices map
        if (vertices.containsKey(first) && vertices.containsKey(second)) {
            val startV = vertices[first]
            val destV = vertices[second]
            startV!!.neighbors[destV!!] = weight //we assure that vertices are non-nullable, since we checked if the key is present. since we can only add Vertex with a key, if key is present so is a vertex
            destV.neighbors[startV] = weight
        } else {
            throw IllegalArgumentException()
        }
    }

    fun removeVertex (name:T) {
        if (vertices.containsKey(name)) {
            disconnectAll(name)
            vertices.remove(name)
        }
    }

    fun disconnectVertices(name1: T, name2: T) { //disconnect 2 vertices FROM EACH OTHER
        if (vertices.containsKey(name1) && vertices.containsKey(name2)) {
            if (vertices[name1]!!.neighbors.containsKey(vertices[name2]) && vertices[name2]!!.neighbors.containsKey(vertices[name1])){
                vertices[name1]!!.neighbors.remove(vertices[name2])
                vertices[name2]!!.neighbors.remove(vertices[name1])
            }
        }
    }

    fun disconnectAll(name:T) { //disconnect vertex from all other vertices
        if (vertices.containsKey(name) && vertices[name]!!.neighbors.isNotEmpty()) {
            for (neighbor in vertices[name]!!.neighbors.keys) {
                neighbor.neighbors.remove(vertices[name])
            }
            vertices[name]!!.neighbors.clear()
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
            return mutableMapOf() //return empty map if vertex is null

    }

    fun findMinSpanTreePrim(): MinimumSpanningTree<T> { //finding of a minimal spanning tree using Prim's algorithm.
        val visited = mutableSetOf<T>()                 //when using Prim's algorithm we choose any vertex as a starting point
        val minimumSpanningTree = MinimumSpanningTree<T>()  //then we compare every incident edge by weight and add it to a spanning tree
        if (vertices.isEmpty()) {                           //if they are not in the same connectivity component
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


    fun findMinSpanTreeKruskal(): MinimumSpanningTree<T> { //finding minimum spanning tree using Kruskal's algorithm and class UnionFind
        val minimumSpanningTree = MinimumSpanningTree<T>() //here we sort all edges by their weight in ascending order. we add the lightest edges to
        if (vertices.isEmpty()) {                          // a spanning tree if it won't result in a cycle forming. we check that by assuring that
            return minimumSpanningTree                     // two vertices incident to our edge don't belong to the same connectivity component
        }
        val allEdges = mutableListOf<Pair<Pair<T, T>, Int>>() // edge consists of a pair of vertices and its weight
        for ((name1, vertex1) in vertices) {
            for ((vertex2, weight) in vertex1.neighbors) {
                if (allEdges.contains(Pair(Pair(vertex2.name, name1), weight))){ //we check if this edge is already used, but in different order
                    continue                                                     //for example, we don't need edge "3--1" if we already have "1--3"
                }
                val edge = Pair(Pair(name1, vertex2.name), weight)
                allEdges.add(edge)
            }
        }

        val sortedEdges = allEdges.sortedBy { it.second } //sorting all edges by their weight in ascending order

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



