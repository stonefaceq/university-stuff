import java.lang.IllegalArgumentException

class Graph {
    private data class Vertex(val name: String) {
        val neighbours = mutableSetOf<Vertex>()
    }

    private val vertices = mutableMapOf<String, Vertex>()
    fun addVertex(name: String) {
        vertices[name] = Vertex(name)
    }
    fun connectVertex (name1: String, name2: String){
        if (name1 !in vertices || name2 !in vertices) {
            throw Exception("invalid argument")
        }
        Vertex(name1).neighbours.add(Vertex(name2))
        Vertex(name2).neighbours.add(Vertex(name1))
    }

}
