import java.util.HashMap;
//207651027
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class RegexOne extends Regex {

    private final String regexOne = "<np>[^<]+</np> (, )?such as <np>[^<]+</np>( (, )"
           + "?<np>[^<]+</np>)*(( ,)? (and|or) <np>[^<]+</np>)?";

    @Override
    public HashMap<String, HashMap<String, Integer>> splitString(String line) {
        return super.splitString(line);
    }
    @Override
    public String getRegex() {
        return this.regexOne;
    }
}
