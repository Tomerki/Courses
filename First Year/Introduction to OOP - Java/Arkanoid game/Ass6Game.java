import animation.AnimationRunner;
import interfaces.LevelInformation;
import levels.DirectHit;
import levels.FinalFour;
import levels.GreenLevel;
import levels.WideEasy;
import supportobjects.GameFlow;

import java.util.ArrayList;
import java.util.List;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Ass6Game {
    /**
     * main that define new game object, initialize new game and run it.
     * @param args - empty
     */
    public static void main(String[] args) {
        GameFlow game = new GameFlow(new AnimationRunner());
        List<LevelInformation> list = new ArrayList<>();
        for (String arg : args) {
            if (arg.equals("1")) {
                list.add(new DirectHit());
            }
            else if (arg.equals("2")) {
                list.add(new WideEasy());
            }
            else if (arg.equals("3")) {
                list.add(new GreenLevel());
            }
            else if (arg.equals("4")) {
                list.add(new FinalFour());
            }
        }
        if (list.isEmpty()) {
            list.add(new DirectHit());
            list.add(new WideEasy());
            list.add(new GreenLevel());
            list.add(new FinalFour());
        }
        game.runLevels(list);
    }
}
