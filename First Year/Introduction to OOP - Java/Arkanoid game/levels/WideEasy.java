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

public class WideEasy implements LevelInformation {

    @Override
    public int numberOfBalls() {
        return 10;
    }

    @Override
    public List<Velocity> initialBallVelocities() {
        List<Velocity> list = new ArrayList<>();
        for (int i = 0, j = -5, k = -4; i < 5; i++, j++, k--) {
            Velocity v = new Velocity(j, k);
            list.add(v);
        }
        for (int i = 0, j = 5, k = -4; i < 5; i++, j--, k--) {
            Velocity v = new Velocity(j, k);
            list.add(v);
        }
        return list;
    }
    @Override
    public int paddleSpeed() {
        return 5;
    }
    @Override
    public int paddleWidth() {
        return 600;
    }
    @Override
    public String levelName() {
        return "Wide Easy";
    }
    @Override
    public Sprite getBackground() {
        return new Block(new Rectangle(new Point(0, 0), 800, 600), Color.white);
    }
    @Override
    public List<Block> blocks() {
        Random rand = new Random();
        Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
        List<Block> list = new ArrayList<>();
        for (int i = 1, j = 40; i <= 12; i++, j += 60) {
            Block b = new Block(new Rectangle(new Point(j, 240), 60, 25), randomColor);
            list.add(b);
            if (i % 2 == 0) {
                randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
            }
        }
        return list;
    }
    @Override
    public int numberOfBlocksToRemove() {
        return 10;
    }
}
