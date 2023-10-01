class NonCanonicBook(bname: String, year: String, author : String) : Book(bname, year, author) {
     override var canonicity = CanonicEnums.NONCANONIC

    override var annotation = "$name is a non-canonic book written by $author and published in year $year. It belongs to collection and includes this characters: "

    override fun showBookData() {
        println(annotation)
        printCharacters()
    }
}
