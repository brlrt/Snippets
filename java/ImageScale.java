import javax.microedition.lcdui.Image;

public class ImageScale {
	/**
	 * @param rgb Source image RGB
	 * @param dstW Scale to this width
	 * @param dstH Scale to this height
	 */
	public static Image scale(Image i, int dstW, int dstH) {
		int w=i.getWidth(), h=i.getHeight();
		int[] srcRGB=new int[w*h];
		int len=srcRGB.length;

		i.getRGB(srcRGB, 0, w, 0, 0, w, h);

		int[] dstRGB=new int[dstW*dstH];
		int dstLen=dstRGB.length;

		int lineChg=(dstH*100)/h, colChg=(dstW*100)/w;
		int col=-1, line=0, idx;

		for (int s=0; s<dstLen; s++) {
			col=(col+1)%dstW;
			if (col==0) {
				line++;
			}

			idx=(w*((line*100)/lineChg))+((col*100)/colChg);
			if (idx>=len) {
				idx=len-1;
			}
			if (idx<0) {
				idx=0;
			}

			dstRGB[s]=srcRGB[idx];
		}

		i=Image.createRGBImage(dstRGB, dstW, dstH, true);
		srcRGB=null;
		dstRGB=null;
		return i;
	}
}
