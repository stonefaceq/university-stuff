import java.lang.IllegalArgumentException
//class used to store info about books, characters, year of creation, author.
abstract class Book(val name : String, val year: String, val author: String) {
    open lateinit var canonicity : CanonicEnums
    val characters = mutableMapOf<String, RoleEnums>("John Doe" to RoleEnums.MAIN, "Jane Doe" to RoleEnums.SECONDARY, "Bob" to RoleEnums.EPISODIC)// here we can access character's role by their name

    fun createCharacter(name: String, role: String) {
        role.lowercase()
        val character : Character = when(role) {
            "main" -> Character(name, RoleEnums.MAIN)
            "secondary" -> Character(name, RoleEnums.SECONDARY)
            "episodic" -> Character(name, RoleEnums.EPISODIC)
            else -> throw IllegalArgumentException()
        }
        characters.put(name, character.role)
    }

    fun addCharacter(character : Character) {
        characters.put(character.name, character.role)
    }
    open var annotation : String = ""

    fun printCharacters() {
        for (hero in characters) {
            println("Hero name: ${hero.key}, hero role: ${hero.value}")
        }
    }

    fun createBookGraph()  {
        val Bgraph1 = Graph<Book>()
    }
    abstract fun showBookData(name: String)

    override fun toString(): String {
        return name
    }
}