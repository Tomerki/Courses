import java.util.ArrayList;
//207651027
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class Patterns {
    /**
     *class that make a list with all our regex.
     */
    private final ArrayList<RegexInter> regexesArray;

    /**
     * constructor to initialize our list and add the regex.
     */
    public Patterns() {
        regexesArray = new ArrayList<>();
        regexesArray.add(new RegexOne());
        regexesArray.add(new RegexTwo());
        regexesArray.add(new RegexThree());
        regexesArray.add(new RegexFour());
        regexesArray.add(new RegexFive());
    }

    /**
     * getter to have an access out side of the class to the list of the regex.
     * @return the list of the regex.
     */
    public ArrayList<RegexInter> getPatternsArray() {
        return regexesArray;
    }
}
