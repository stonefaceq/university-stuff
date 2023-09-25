fun main() {
    val g = Graph()
    g.addVertex("A")
    g.addVertex("B")
    g.addVertex("C")
    g.addVertex("D")
    g.connectVertex("A", "C")
    g.connectVertex("B", "D")
    g.connectVertex("B", "C")

}