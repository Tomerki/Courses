package levels;
import geometry.Point;
import geometry.Rectangle;
import interfaces.LevelInformation;
import interfaces.Sprite;
import sprites.Block;
import supportobjects.Velocity;
import java.awt.Color;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class GreenLevel implements LevelInformation {
    @Override
    public int numberOfBalls() {
        return 2;
    }

    @Override
    public List<Velocity> initialBallVelocities() {
        List<Velocity> list = new ArrayList<>();
        Velocity v1 = new Velocity(-4, -6);
        Velocity v2 = new Velocity(4, -6);
        list.add(v1);
        list.add(v2);
        return list;
    }

    @Override
    public int paddleSpeed() {
        return 11;
    }

    @Override
    public int paddleWidth() {
        return 100;
    }

    @Override
    public String levelName() {
        return "The Green Stage";
    }

    @Override
    public Sprite getBackground() {
        return new Block(new Rectangle(new Point(0, 0), 800, 600), Color.GREEN);
    }

    @Override
    public List<Block> blocks() {
        Random rand = new Random();
        Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
        List<Block> list = new ArrayList<>();
        int newXValue = 0;
        int newYValue = 0;
        for (int i = 10; i >= 6; i--) {
            for (int j = i; j > 0; j--) {
                Block b = new Block(new Rectangle(new Point(715 - newXValue, 150 + newYValue), 45, 25), randomColor);
                list.add(b);
                newXValue += 45;
            }
            randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
            newYValue += 25;
            newXValue = 0;
        }
        return list;
    }
    @Override
    public int numberOfBlocksToRemove() {
        return 40;
    }
}
