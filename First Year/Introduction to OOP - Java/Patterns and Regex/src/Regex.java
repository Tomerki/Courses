import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
//207651027
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public abstract class Regex implements RegexInter {

    @Override
    public HashMap<String, HashMap<String, Integer>> splitString(String line) {
        HashMap<String, HashMap<String, Integer>> mapping = new HashMap<>();
        String s = Pattern.quote("<np>") + "(.*?)" + Pattern.quote("</np>");
        Pattern pattern = Pattern.compile(s);
        Matcher matcher = pattern.matcher(line);
        matcher.find();
        String myValue = matcher.group(1);
        mapping.put(myValue, new HashMap<>());
        while (matcher.find()) {
            if (mapping.get(myValue).containsKey(matcher.group(1))) {
                mapping.get(myValue).put(matcher.group(1), mapping.get(myValue).get(matcher.group(1)) + 1);
            } else {
                mapping.get(myValue).put(matcher.group(1), 1);
            }
        }
        return mapping;
    }
}
