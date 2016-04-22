/**
 * Created by ikrukov on 4/7/2016.
 */
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;

public class ImageDrawer extends JPanel{

    private BufferedImage image;

    public ImageDrawer(BufferedImage image) {
        this.image = image;
        this.setVisible(true);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, null); // see javadoc for more info on the parameters
    }

}
