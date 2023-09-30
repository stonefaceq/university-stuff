import java.lang.IllegalArgumentException
//class for book collections. two (or more) books belong to the same collection if they share at least one common character
class BookCollection {
    //collection itself is a graph that includes all books in it. i wanted to make it so the weight of an edge would represent
    // the number of common characters, but didn't have enough time.
    private val bookGraphs = mutableSetOf<Graph<Book>>()
    //we look through each graph (collections), through each bouk in that collection and then through each characters in that book
    //if at least 1 character from our book matches, our book will be added to collection which other book belongs to
    fun addBookToCol(book: Book) {
        lateinit var graphChange : Graph<Book>
        var same : Boolean = false
        for (graph in bookGraphs) {
            graphChange = graph
            for(book1 in graph.vertices) {
                for(hero1 in book.characters.keys)
                    for (hero2 in book1.key.characters.keys) {
                        same = hero1 == hero2

                    }

            }
        }

        when(same) {
            true -> graphChange.addVertex(book)
            false -> {val graph =  Graph<Book>()
            graph.addVertex(book)
                    bookGraphs.add(graph)}
        }

    }

    fun printCollections() {
        for (collection in bookGraphs) {
            println(collection.vertices.keys.toString())
        }
    }
}