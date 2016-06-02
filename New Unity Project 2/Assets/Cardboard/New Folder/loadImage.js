#pragma strict

var epochStart = new System.DateTime(1970, 1, 1, 0, 0, 0, System.DateTimeKind.Utc);
var cur_time = (System.DateTime.UtcNow - epochStart).TotalSeconds;
var url = "http://192.168.1.5/picam/cam_pic.php?time=" + cur_time * 1000;

function Start () {
	// Create a texture in DXT1 format
	GetComponent.<Renderer>().material.mainTexture = new Texture2D(4, 4, TextureFormat.DXT1, false);
        
	while(true) {
		// Start a download of the given URL
		var www = new WWW(url);

		// wait until the download is done
		yield www;

		// assign the downloaded image to the main texture of the object
		www.LoadImageIntoTexture(GetComponent.<Renderer>().material.mainTexture);
	}
}

function Update () {

}