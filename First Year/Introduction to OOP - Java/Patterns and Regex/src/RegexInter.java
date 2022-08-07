import java.util.HashMap;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public interface RegexInter {

    /**
     * this method roll is to split the string that our regex found into an hypernym and all his hyponym,
     * and save it in a map such that the hypernym is the key and the value is a map that the hyponym
     * using as a key in this internal map and the number of time its appear is the value.
     * @param s - the string that our regex found.
     * @return - map with all the hypernym and their hyponym as i describe.
     */
    HashMap<String, HashMap<String, Integer>> splitString(String s);

    /**
     * getter to have an access to the regex string.
     * @return the string that describe the regex.
     */
    String getRegex();
}
