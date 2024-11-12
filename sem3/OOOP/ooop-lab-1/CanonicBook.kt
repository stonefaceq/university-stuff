class CanonicBook(bname: String, year: String, author : String) : Book(bname, year, author) {
    override var canonicity = CanonicEnums.CANONIC
    override var annotation = "$name is a canonic book written by $author and published in year $year. Book includes this characters: "

    override fun showBookData() {
        println(annotation)
        printCharacters()
    }
}