fun main() {
    val g = Graph<Int>()
   try {
       g.addVertex(1)
       g.addVertex(2)
       g.addVertex(3)
       g.addVertex(4)
       g.connectVertex(1, 3, 5)
       g.connectVertex(3, 4, 6)
       g.connectVertex(1, 2, 7)
       g.showNeighbors(1)

   } catch (e: IllegalArgumentException) {
       println("Illegal argument exception.")
   }
}