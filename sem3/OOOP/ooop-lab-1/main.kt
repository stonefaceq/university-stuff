fun main() {
    val g = Graph<Book>()
   try {
       val book1 = CanonicBook("One Piece", "1984", "author")
       val book2 = AlternativeBook("Naruto", "1985", "author")
       val book3 = CanonicBook("Bleach", "1986", "author")
       val book4 = CanonicBook("Jujutsu Kaisen", "1988", "author")
       val collection = BookCollection()


        book1.createCharacter("John Doe", "secondary")
        book1.createCharacter("Jane Doe", "main")
        book2.createCharacter("John Doe", "main")
        book3.createCharacter("Jane Doe", "secondary")
        book3.createCharacter("Bob", "main")

        book1.showBookData()
       book1.printCharacters()
       collection.addBookToCol(book1)
       collection.addBookToCol(book2)
       collection.addBookToCol(book4)
       collection.printCollections()



        println("___________________")

   } catch (e: IllegalArgumentException) {
       println("Illegal argument exception.")
   }
}