import java.lang.IllegalArgumentException

class Graph<T> {
    private data class Vertex<T>(val name: T) {
        val neighbors = mutableSetOf<Vertex<T>>()
    }

    private val vertices = mutableMapOf<T, Vertex<T>>()

    fun addVertex(name: T) {

            vertices[name] = Vertex(name)

    }
    fun connectVertex(first: T, second: T) {
        if(vertices.containsKey(first) && vertices.containsKey(second)) {
            val startV = vertices[first]
            val destV = vertices[second]
            startV!!.neighbors.add(destV!!)
            destV.neighbors.add(startV)
        }
        else {
            throw IllegalArgumentException()
        }
    }
    fun neighbors(name: T): List<T> {
        val vertex = vertices[name]
        return vertex?.neighbors?.map { it.name  } ?: listOf()
    }

    fun showNeighbors(name: T) {
        println(neighbors(name))
    }

    private operator fun get(name: T) : Vertex<T> {
        return vertices[name] ?: throw IllegalArgumentException()
    }

}


