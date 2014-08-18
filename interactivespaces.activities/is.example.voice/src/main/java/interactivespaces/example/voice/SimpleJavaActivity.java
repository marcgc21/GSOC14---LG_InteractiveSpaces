package interactivespaces.example.voice;

import java.util.Map;

import com.google.common.collect.Maps;

import interactivespaces.activity.impl.web.BaseWebActivity;

/**
 * A simple Interactive Spaces Java-based activity.
 */
public class SimpleJavaActivity extends BaseWebActivity {

	@Override
	public void onActivityActivate() {
		sendImageUrl("img/activate.jpg");
	}

	@Override
	public void onActivityDeactivate() {
		sendImageUrl("img/deactivate.jpg");
	}


	private void sendImageUrl(String imageUrl) {
		Map<String, Object> data = Maps.newHashMap();
		data.put("imageUrl", imageUrl);

		// Send data to all websocket connections
		sendAllWebSocketJson(data);
	}

	@Override
	public void onNewWebSocketConnection(String connectionId) {
		getLog().info(
				"Got web socket connection from connection " + connectionId);
	}

	@Override
	public void onWebSocketClose(String connectionId) {
		getLog().info("Got web socket close from connection " + connectionId);
	}

	@Override
	public void onWebSocketReceive(String connectionId, Object d) {
		getLog().info("Got web socket data from connection " + connectionId);
		
		Map<String, Object> data = (Map<String, Object>)d;
		getLog().info(data);
	}
}
