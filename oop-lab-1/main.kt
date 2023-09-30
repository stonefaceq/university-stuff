fun main() {
    val g = Graph<Book>()
   try {
       val book1 = CanonicBook("One Piece", "1984", "author")
       val book2 = AlternativeBook("Naruto", "1985", "author")
       val book3 = CanonicBook("Bleach", "1986", "author")
       val book4 = CanonicBook("Jujutsu Kaisen", "1988", "author")
       val collection = BookCollection()
       collection.addBookToCol(book1)
       collection.addBookToCol(book2)
       collection.addBookToCol(book4)
       collection.printCollections()
       println(book1.annotation)
        book2.createCharacter("John Doe", "secondary")
        book2.createCharacter("Jane Doe", "main")
        book2.printCharacters()
        g.addVertex(book1)
        g.addVertex(book2)
        g.addVertex(book3)
        g.addVertex(book4)
        g.connectVertex(book1, book2, 1)
        g.connectVertex(book1, book4, 1)
        g.connectVertex(book2, book4, 1)
        g.connectVertex(book4, book3, 1)
        g.showNeighbors(book1)
        println("___________________")

   } catch (e: IllegalArgumentException) {
       println("Illegal argument exception.")
   }
}