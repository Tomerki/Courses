
import java.util.Collections;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.LinkedHashMap;
import java.util.Map;
import static java.util.stream.Collectors.toMap;
//207651027
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class MapClass {
    /**
     * class that initialize a map with Strings key that every key point to a map in his value.
     * and like that we can save hypernym as a key and the value is a map with all the hyponym
     * of that hypernym. and the values of the hyponym in the internal map is the number of time
     * that this hyponym appears as this specific hypernym.
     */
    private final HashMap<String, HashMap<String, Integer>> myDataBase;

    /**
     * constructor to initialize a new Map that store in it our data.
     */
    public MapClass() {
        this.myDataBase = new HashMap<>();
    }

    /**
     * this method roll is to add an element in the correct way,
     * means that if we need to insert a key and value that is already in the map
     * we just update the value, otherwise we add the new element.
     * @param key - the key of the element to insert.
     * @param map - the value of the element to insert.
     */
    public void addElement(String key, HashMap<String, Integer> map) {
        //check if the key element in the map.
        if (this.myDataBase.containsKey(key)) {
            for (String s : map.keySet()) {
                if (this.myDataBase.get(key).containsKey(s)) {
                    this.myDataBase.get(key).put(s, this.myDataBase.get(key).get(s) + map.get(s));
                } else {
                    this.myDataBase.get(key).put(s, map.get(s));
                }
            }
            return;
        }
        //add the new element if doesn't appear yet.
        this.myDataBase.put(key, map);
    }

    /**
     * getter to have an access to the field outside the class.
     * @return - the field myDataBase that contained all the data that we read from the text.
     */
    public HashMap<String, HashMap<String, Integer>> getMyDataBase() {
        return myDataBase;
    }

    /**
     * method to remove all the hypernym that has less then 3 hyponym.
     */
    public void removeKeys() {
        //made a copy of the map to be able to iterate elements while removing elements.
        HashMap<String, HashMap<String, Integer>> tempMap = new HashMap<>(this.myDataBase);
        for (String s : tempMap.keySet()) {
            if (this.myDataBase.get(s).keySet().size() < 3) {
                this.myDataBase.remove(s);
            }
        }
    }

    /**
     * the method put the hash map into a treemap and than sort all the Integers value of the
     * map that uses as a value of the keys in the main map.
     * and like that we get a map the sort in case insensitive order and sorted in the Integers values
     * @return a new map with the same element like our original map.
     */
    public TreeMap<String, HashMap<String, Integer>> sortMap() {
        //sort with tree map the keys of the map in case insensitive order.
        TreeMap<String, HashMap<String, Integer>> sortedMap = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
        sortedMap.putAll(this.myDataBase);
        //sort the internal map by the value.
        for (String s: this.myDataBase.keySet()) {
            //using stream and collect the sorted map in to a linkHaseMap.
            HashMap<String, Integer> map = sortedMap.get(s).entrySet().stream()
                    .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                    .collect(toMap(Map.Entry::getKey, Map.Entry::getValue,
                            (myValue, myNewValue) -> myNewValue, LinkedHashMap::new));
            sortedMap.put(s, map);
        }
        return sortedMap;
    }
}
