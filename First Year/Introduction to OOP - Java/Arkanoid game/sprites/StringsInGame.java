package sprites;
import animation.GameLevel;
import biuoop.DrawSurface;
import interfaces.Sprite;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class StringsInGame implements Sprite {
    private final GameLevel game;

    /**
     * create new StringsGame object that responsible on the texts in the game.
     * @param g - the level we want to show its name.
     */
    public  StringsInGame(GameLevel g) {
        this.game = g;
    }
    @Override
    public void drawOn(DrawSurface d) {
        d.drawText(500, 20, "Level Name: " + this.game.getLevelInfo().levelName(), 15);
        d.drawText(80, 20, "Lives: " + this.game.getLives().getValue(), 15);
    }
    @Override
    public void timePassed() {
    }
}
