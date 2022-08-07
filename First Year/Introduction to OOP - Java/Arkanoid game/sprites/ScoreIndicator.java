package sprites;
import biuoop.DrawSurface;
import interfaces.Sprite;
import supportobjects.Counter;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class ScoreIndicator implements Sprite {
    static final int TEXT_X_POSITION = 300;
    static final int TEXT_Y_POSITION = 20;
    static final int TEXT_SIZE = 15;
    private final Counter score;

    /**
     * constructor creating an object that showing on the screen the player score and get update when needed.
     * @param score - Counter object with the current score of the game.
     */
    public ScoreIndicator(Counter score) {
        this.score = score;
    }

    @Override
    public void drawOn(DrawSurface d) {
        d.drawText(TEXT_X_POSITION, TEXT_Y_POSITION, "Score: " + score.getValue(), TEXT_SIZE);
    }
    @Override
    public void timePassed() {
    }
}
