using System;
using System.IO;
using System.Net;
using System.Security.Cryptography;
using System.Text;

namespace Mvno.WebApplications
{
	public class Twitter
	{
		private const string _consumerKey = "insert your consumer key here";
		private const string _consumerSecret = "insert your consumer secret here";
		private const string _accessToken = "insert your access token here";
		private const string _accessTokenSecret = "insert your access token secret here";
		private const string _publishUrl = "https://api.twitter.com/1/statuses/update.json";
		private const string _oauthSignatureMethod = "HMAC-SHA1";
		private const string _oauthVersion = "1.0";

		public string Tweet(string status)
		{
			var nonce = GetOAuthNonce();
			var timestamp = GetOAuthTimeStamp();
			var parameterString = GetParameterString(nonce, timestamp, status);
			var signingKey = GetSigningKey();
			var signature = GetSignature(signingKey, parameterString);
			var authorizationHeader = GetAuthorizationHeader(nonce, signature, timestamp);

			var webRequest = GetWebRequest(authorizationHeader);

			SendTweet(webRequest, status);
			return ReadResponse(webRequest);
		}

		private string GetOAuthNonce()
		{
			return Guid.NewGuid().ToString().Replace("-", "");
		}

		private string GetOAuthTimeStamp()
		{
			var timeStamp = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);

			return Convert.ToInt64(timeStamp.TotalSeconds).ToString();
		}

		private string GetParameterString(string nonce, string timestamp, string status)
		{
			var parameterString = "POST&" + Uri.EscapeDataString(_publishUrl) + "&";

			// Must be in alphabetical order
			parameterString += Uri.EscapeDataString("oauth_consumer_key=" + _consumerKey + "&");
			parameterString += Uri.EscapeDataString("oauth_nonce=" + nonce + "&");
			parameterString += Uri.EscapeDataString("oauth_signature_method=" + _oauthSignatureMethod + "&");
			parameterString += Uri.EscapeDataString("oauth_timestamp=" + timestamp + "&");
			parameterString += Uri.EscapeDataString("oauth_token=" + _accessToken + "&");
			parameterString += Uri.EscapeDataString("oauth_version=" + _oauthVersion + "&");
			parameterString += Uri.EscapeDataString("status=" + Uri.EscapeDataString(status));

			return parameterString;
		}

		private string GetSigningKey()
		{
			return Uri.EscapeDataString(_consumerSecret) + "&" + Uri.EscapeDataString(_accessTokenSecret);
		}

		private string GetSignature(string signingKey, string parameterString)
		{
			var hasher = new HMACSHA1(new ASCIIEncoding().GetBytes(signingKey));

			return Convert.ToBase64String(hasher.ComputeHash(new ASCIIEncoding().GetBytes(parameterString)));
		}

		private string GetAuthorizationHeader(string nonce, string signature, string timestamp)
		{
			var authorizationHeader = "OAuth ";

			// Must be in alphabetical order
			authorizationHeader += string.Format("oauth_consumer_key={0}{1}{2}, ", '"', Uri.EscapeDataString(_consumerKey), '"');
			authorizationHeader += string.Format("oauth_nonce={0}{1}{2}, ", '"', Uri.EscapeDataString(nonce), '"');
			authorizationHeader += string.Format("oauth_signature={0}{1}{2}, ", '"', Uri.EscapeDataString(signature), '"');
			authorizationHeader += string.Format("oauth_signature_method={0}{1}{2}, ", '"', Uri.EscapeDataString(_oauthSignatureMethod), '"');
			authorizationHeader += string.Format("oauth_timestamp={0}{1}{2}, ", '"', Uri.EscapeDataString(timestamp), '"');
			authorizationHeader += string.Format("oauth_token={0}{1}{2}, ", '"', Uri.EscapeDataString(_accessToken), '"');
			authorizationHeader += string.Format("oauth_version={0}{1}{2}", '"', Uri.EscapeDataString(_oauthVersion), '"');

			return authorizationHeader;
		}

		private HttpWebRequest GetWebRequest(string authorizationHeader)
		{
			ServicePointManager.Expect100Continue = false;		// We can't do 100 continue
			var webRequest = (HttpWebRequest)WebRequest.Create(_publishUrl);

			webRequest.KeepAlive = false;
			webRequest.Headers.Add("Authorization", authorizationHeader);
			webRequest.Method = "POST";
			webRequest.ContentType = "application/x-www-form-urlencoded";

			return webRequest;
		}
	
		private void SendTweet(WebRequest webRequest, string status)
		{
			var postBody = "status=" + Uri.EscapeDataString(status);
			var stream = webRequest.GetRequestStream();
			byte[] bodyBytes = new ASCIIEncoding().GetBytes(postBody);
			stream.Write(bodyBytes, 0, bodyBytes.Length);
			stream.Flush();
			stream.Close();
		}

		private string ReadResponse(WebRequest webRequest)
		{
			webRequest.Timeout = 3 * 60 * 1000;
			var webResponse = (HttpWebResponse)webRequest.GetResponse();

			return new StreamReader(webResponse.GetResponseStream()).ReadToEnd();
		}
	}
}
