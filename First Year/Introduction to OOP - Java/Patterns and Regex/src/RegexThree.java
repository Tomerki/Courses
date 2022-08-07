import java.util.HashMap;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class RegexThree extends Regex {

    private final String regexThree = "<np>[^<]+</np>( ,)? including <np>[^<]+</np>"
           + "( (, )?<np>[^<]+</np>)*(( ,)? (and|or) <np>[^<]+</np>)?";

    @Override
    public HashMap<String, HashMap<String, Integer>> splitString(String line) {
        return super.splitString(line);
    }

    @Override
    public String getRegex() {
        return this.regexThree;
    }
}
