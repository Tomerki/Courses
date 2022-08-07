import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class CreateHypernymDatabase {
    /**
     * main metheod that read the data in the directory that we get as argument in args[0]
     * and than write all the data that we collect in our map to a new file that we get as argument in args[1].
     * @param args - list of strings that we get the path to the relevant files.
     * @throws IOException - throws exception if something got wrong with reading the file.
     */
    public static void main(String[] args) throws IOException {
        MapClass myMap = new MapClass();
        Patterns myPatterns = new Patterns();
        BufferedReader bReader = null;
        try {
            File myFolder = new File(args[0]);
            File[] fileList = myFolder.listFiles();
            assert fileList != null;
            for (File f : fileList) {
                bReader = new BufferedReader(new FileReader(f));
                String oneLine;
                while ((oneLine = bReader.readLine()) != null) {
                    for (RegexInter r : myPatterns.getPatternsArray()) {
                        Pattern pattern = Pattern.compile(r.getRegex());
                        Matcher matcher = pattern.matcher(oneLine);
                        while (matcher.find()) {
                            Set<String> tempSet = r.splitString(oneLine
                                    .substring(matcher.start(), matcher.end())).keySet();
                            myMap.addElement(tempSet.toArray()[0].toString(), r.splitString(oneLine
                                    .substring(matcher.start(), matcher.end())).get(tempSet.toArray()[0].toString()));
                        }
                    }
                }
            }
            //catch the exception if we got one.
        } catch (IOException | RuntimeException e) {
            e.printStackTrace();
        //insure that we close the file.
        } finally {
            if (bReader != null) {
                bReader.close();
            }
        }
        //remove the hypernym.
        myMap.removeKeys();
        TreeMap<String, HashMap<String, Integer>> sortedMap = new TreeMap<>(myMap.sortMap());
        BufferedWriter bWriter = null;
        try {
            bWriter = new BufferedWriter(new FileWriter(args[1]));
            //iterate through the sorted map and write the data to a file.
            for (String s : sortedMap.keySet()) {
                StringBuilder fixString = new StringBuilder();
                fixString.append(s).append(":");
                for (Map.Entry<String, Integer> s1 : sortedMap.get(s).entrySet()) {
                    fixString.append(" ").append(s1.getKey()).append(" (")
                            .append(s1.getValue()).append(")").append(",");
                }
                fixString.deleteCharAt(fixString.length() - 1);
                bWriter.write(String.valueOf(fixString));
                bWriter.write("\n");
            }
        } catch (IOException | RuntimeException e) {
            e.printStackTrace();
        //insure that the files get close.
        } finally {
            if (bWriter != null) {
                bWriter.close();
            }
            if (bReader != null) {
                bReader.close();
            }
        }
    }
}



