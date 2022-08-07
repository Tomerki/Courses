package interfaces;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public interface HitNotifier {
    /**
     * Add hitlistener as a listener to hit events.
     * @param hl - the hl to add.
     */
    void addHitListener(HitListener hl);
    /**
     * Remove hl from the list of listeners to hit events.
     * @param hl = the hl to remove.
     */
    void removeHitListener(HitListener hl);
}
