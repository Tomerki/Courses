import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
//207651027
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class DiscoverHypernym {
    /**
     * the class reading from the files that we get as argument there path in args[0],
     * and collect the data on the specific lemma that we got as argument as well in the args[1].
     * @param args - list of strings that contained the path to the files and the lemma.
     * @throws IOException - throws exception if something got wrong while reading the texts.
     */
    public static void main(String[] args) throws IOException {
        MapClass myMap = new MapClass();
        myMap.getMyDataBase().put("LittleMap", new HashMap<>());
        String myLemma = args[1];
        Patterns myPatterns = new Patterns();
        BufferedReader bReader = null;
        if (myLemma.isEmpty()) {
            System.out.println("something go wrong");
        }
        try {
            File myFolder = new File(args[0]);
            File[] fileList = myFolder.listFiles();
            assert fileList != null;
            //reading from the texts
            for (File f : fileList) {
                bReader = new BufferedReader(new FileReader(f));
                String oneLine;
                while ((oneLine = bReader.readLine()) != null) {
                    for (RegexInter r : myPatterns.getPatternsArray()) {
                        Pattern pattern = Pattern.compile(r.getRegex());
                        Matcher matcher = pattern.matcher(oneLine);
                        while (matcher.find()) {
                            if (oneLine.substring(matcher.start(), matcher.end()).contains(myLemma)) {
                                Set<String> tempSet = r.splitString(oneLine
                                        .substring(matcher.start(), matcher.end())).keySet();
                                myMap.addElement(tempSet.toArray()[0].toString(), r.splitString(oneLine
                                        .substring(matcher.start(), matcher.end()))
                                        .get(tempSet.toArray()[0].toString()));
                            }
                        }
                    }
                }
            }
        } catch (IOException | RuntimeException e) {
            e.printStackTrace();
        } finally {
            if (bReader != null) {
                bReader.close();
            }
        }
        printMap(myMap, myLemma);
    }
    /**
     * this method put inside a temp map all the hypernym that we found that the lemma described in the text
     * as type of those hypernym. than we print all the data in the new map.
     * @param map - our MapClass object that have one element - the hypernym of the lemma as a key
     *            and all the hyponym in the internal map.
     * @param lemma - the hyponym that we search all his hypernym.
     */
    public static void printMap(MapClass map, String lemma) {
        HashMap<String, Integer> temp = new HashMap<>();
        for (String s : map.getMyDataBase().keySet()) {
            for (Map.Entry<String, Integer> e : map.getMyDataBase().get(s).entrySet()) {
                //if the lemma already exist we just update the value.
                if (e.getKey().equals(lemma)) {
                    if (temp.containsKey(s)) {
                        temp.replace(s, e.getValue(), e.getValue() + 1);
                    } else {
                        temp.put(s, e.getValue());
                    }
                }
            }
        }
        MapClass m = new MapClass();
        m.getMyDataBase().put("1", temp);
        //print all the data in sorted order.
        for (Map.Entry<String, Integer> s1 : m.sortMap().get("1").entrySet()) {
            System.out.println(s1.getKey() + ": " + "(" + s1.getValue() + ")" + "\n");
        }
    }
}
