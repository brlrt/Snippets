		TweetThis(serviceStatusViewModel.Content);

		.
		.
		.

		private void TweetThis(string content)
		{
			var tweet = GetTrimmedContent(content);
			var index = 0;
			while (index < tweet.Length)
			{
				var tweetLength = tweet.Length - index;
				if (tweetLength > 128)
				{
					tweetLength = 128;
				}

				var message = tweet.Substring(index, tweetLength);
				index += tweetLength;
				if (tweet.Length - index > 0)
				{
					message += " ... mere";
				}

				var twitter = new Twitter();
				twitter.Tweet(message);
				Thread.Sleep(250);
			}
		}

		private string GetTrimmedContent(string content)
		{
			content = Regex.Replace(content, "<.*?>", string.Empty);
			content = Regex.Replace(content, "&.*;", string.Empty);
			return Regex.Replace(content, "[^a-zA-Z0-9 -]", string.Empty).Trim();
		}
