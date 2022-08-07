package levels;
import geometry.Point;
import geometry.Rectangle;
import interfaces.LevelInformation;
import interfaces.Sprite;
import sprites.Block;
import supportobjects.Velocity;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.awt.Color;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class FinalFour implements LevelInformation {
    @Override
    public int numberOfBalls() {
        return 3;
    }

    @Override
    public List<Velocity> initialBallVelocities() {
        List<Velocity> list = new ArrayList<>();
        Velocity v1 = new Velocity(-3, -5);
        Velocity v2 = new Velocity(0, -6);
        Velocity v3 = new Velocity(3, -5);
        list.add(v1);
        list.add(v2);
        list.add(v3);
        return list;
    }

    @Override
    public int paddleSpeed() {
        return 13;
    }

    @Override
    public int paddleWidth() {
        return 100;
    }

    @Override
    public String levelName() {
        return "Final Blue Stage";
    }

    @Override
    public Sprite getBackground() {
        return new Block(new Rectangle(new Point(0, 0), 800, 600), Color.blue);
    }

    @Override
    public List<Block> blocks() {
        Random rand = new Random();
        Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
        List<Block> list = new ArrayList<>();
        int newXValue = 0;
        int newYValue = 0;
        for (int i = 7; i > 0; i--) {
            for (int k = 0; k < 15; k++) {
                Block b = new Block(new Rectangle(new Point(712 - newXValue, 100 + newYValue), 48, 25), randomColor);
                list.add(b);
                newXValue += 48;
            }
            randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
            newYValue += 25;
            newXValue = 0;
        }
        return list;
    }

    @Override
    public int numberOfBlocksToRemove() {
        return 105;
    }
}
