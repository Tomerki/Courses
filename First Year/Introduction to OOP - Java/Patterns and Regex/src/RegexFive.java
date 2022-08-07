import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
//207651027
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class RegexFive extends Regex {

    private final String regexFive = "<np>[^<]+</np>( ,)? which is"
           + " ((an example|a kind|a class) of)?<np>[^<]+</np>";

    @Override
    public HashMap<String, HashMap<String, Integer>> splitString(String line) {
        HashMap<String, HashMap<String, Integer>> mapping = new HashMap<>();
        String s = Pattern.quote("<np>") + "(.*?)" + Pattern.quote("</np>");
        Pattern pattern = Pattern.compile(s);
        Matcher matcher = pattern.matcher(line);
        matcher.find();
        String myValue = matcher.group(1);
        matcher.find();
        String myKey = matcher.group(1);
        HashMap<String, Integer> m = new HashMap<>();
        m.put(myValue, 1);
        mapping.put(myKey, m);
        return mapping;
    }

    @Override
    public String getRegex() {
        return this.regexFive;
    }
}
