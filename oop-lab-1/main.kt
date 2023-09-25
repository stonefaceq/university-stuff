fun main() {
    val g = Graph<Int>()
    g.addVertex(1)
    g.addVertex(2)
    g.addVertex(3)
    g.addVertex(4)
    g.connectVertex(1, 3)
    g.connectVertex(2, 4)
    g.connectVertex(2, 3)
    g.showNeighbors(2)
}