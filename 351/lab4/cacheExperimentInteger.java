
class cacheExperimentInteger {

	public static void main(String[] arg) {
		Integer src[][] = new Integer[4096][4096];
		Integer dst[][] = new Integer[4096][4096];
		
		int rep;
		int i, j;
		
		for ( rep = 0; rep < 10; rep++ ) {
			for ( i = 0; i < 4096; i++) {
				for ( j = 0; j < 4096; j++) {
					src[i][j] = i * rep;
					dst[i][j] = src[i][j];
				}
			}
		}
	}

}
