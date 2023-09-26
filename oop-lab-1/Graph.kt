import java.lang.IllegalArgumentException

class Graph<T> {
    private data class Vertex<T>(val name: T) {
        val neighbors = mutableMapOf<Vertex<T>, Int>()
    }

    private val vertices = mutableMapOf<T, Vertex<T>>()

    fun addVertex(name: T) {

            vertices[name] = Vertex(name)

    }
    fun connectVertex(first: T, second: T, weight:Int) {
        if(vertices.containsKey(first) && vertices.containsKey(second)) {
            val startV = vertices[first]
            val destV = vertices[second]
            startV!!.neighbors[destV!!] = weight
            destV.neighbors[startV] = weight
        }
        else {
            throw IllegalArgumentException()
        }
    }
    private  fun getNeighborMap(name: T): Map<T, Int> {
        val vertex = vertices[name]
        if (vertex != null) {
            val neighborMap = mutableMapOf<T, Int>()
            val neighbors = vertex.neighbors
            for ((neighbor, weight) in neighbors) {
                neighborMap[neighbor.name] = weight
            }
            return neighborMap


        }
        else
            return mutableMapOf()

    }



    fun showNeighbors(name: T) {
        if (this.getNeighborMap(name) !=null)  {
            for ((neighbor, weight) in getNeighborMap(name)) {
                println("neighbor: $neighbor, weight: $weight\n")
            }
        }
        else
            println("error")

    }

    private operator fun get(name: T) : Vertex<T> {
        return vertices[name] ?: throw IllegalArgumentException()
    }

}


