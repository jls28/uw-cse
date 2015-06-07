import java.util.*;

import com.restfb.*;
import com.restfb.types.*;

public class FBPlay {
	public static void main(String[] args) {
		//printPublicPostWithKeyword("Java");
		System.out.println();

		// temporary access token from http://developers.facebook.com/tools/explorer/
		String token = "BAACEdEose0cBAD33ZCDr2QAeX0OcQ6kjQ9TU6lz7ooeuveVFC16wAyIcyKsa99rSxY3jDZADzZCeRZCOomXkHr6paWrEJPBJzUbEgAzxPu01i4fDkId38qoz8YQtgCrzQDUMLQ8Slb0ej5NoxeZAEZB8NZCmcdvTO50QsJ4Exax10XO46oHn1BvJUQvii98wuucDrZAwJg6ArAZDZD";
		List<User> myFriends = getMyFriends(token);

		//printFriendGenders(myFriends);

		// map first names to their frequency
		Map<String, Integer> names = new TreeMap<String, Integer>();
		for (User friend : myFriends) {
			if (names.containsKey(friend.getFirstName())) {
				names.put(friend.getFirstName(),
						names.get(friend.getFirstName()) + 1);
			} else {
				names.put(friend.getFirstName(), 1);
			}
		}
		System.out.println(names);

		// find the most popular first name
		String most = names.keySet().iterator().next();
		for (String name : names.keySet()) {
			if (names.get(name) > names.get(most)) {
				most = name;
			}
		}
		System.out.println("Most popular name: " + most + " ("
				+ names.get(most) + ")");

		// what names map to what frequencies?
		Map<Integer, List<String>> freqs = new TreeMap<Integer, List<String>>();
		for (String name : names.keySet()) {
			if (!freqs.containsKey(names.get(name))) {
				freqs.put(names.get(name), new ArrayList<String>());
			}
			freqs.get(names.get(name)).add(name);
		}

		for (int frequency : freqs.keySet()) {
			System.out.println(frequency + ": " + freqs.get(frequency));
		}
		printStuff();
	}

	// Find posts with the given keyword, print a random one with likes and
	// author
	public static void printPublicPostWithKeyword(String keyword) {
		FacebookClient publicFBClient = new DefaultFacebookClient();
		Connection<Post> search = publicFBClient.fetchConnection("search",
				Post.class, Parameter.with("q", keyword),
				Parameter.with("type", "post"));

		List<Post> posts = search.getData();
		int postCount = posts.size();
		Post rand = search.getData().get((int) (Math.random() * postCount));

		System.out.println(rand.getMessage());

		System.out.println("Likes: " + rand.getLikesCount());
		System.out.println("Author: " + rand.getFrom().getName());
	}
	
	public static void printStuff() {
		String keyword = "math 126";
		FacebookClient client = new DefaultFacebookClient();
		Connection<Post> search = client.fetchConnection("search", Post.class, Parameter.with("q", keyword), 
				Parameter.with("type", "post"));
		List<Post> posts = search.getData();
		System.out.println("Number of posts about: " + keyword + " | " +posts.size());
		int count = 0;
		for(Post i : posts) {
			count++;
			System.out.println(count + ": " + i.getMessage());
		}
		
		
	}

	// returns a list of the authenticated user's friends
	public static List<User> getMyFriends(String token) {
		FacebookClient privateFBClient = new DefaultFacebookClient(token);
		Connection<User> myFriends = privateFBClient.fetchConnection(
				"me/friends", User.class,
				Parameter.with("fields", "first_name, gender"));
		return myFriends.getData();
	}

	// print how many friends are female and how many are male
	public static void printFriendGenders(List<User> myFriends) {
		int male = 0;
		int female = 0;
		System.out.println("Total: " + myFriends.size());
		for (User friend : myFriends) {
			if (friend.getGender() != null) {
				if (friend.getGender().equals("male")) {
					male++;
				} else if (friend.getGender().equals("female")) {
					female++;
				}
			}
		}
		System.out.println("Female: " + female);
		System.out.println("Male: " + male);
	}
}