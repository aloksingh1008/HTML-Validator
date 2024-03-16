#include <bits/stdc++.h> // Include all necessary C++ standard libraries

using namespace std;
stringstream CODE; // stringstream to hold the HTML code
vector<int> checks; // Vector to store validation checks results
int welcomeSection, h1TagText, projectSection, projectTileClass, navBarId, textTillNow, styleTag; // Variables to track different sections and elements in HTML

// Structure to represent HTML tag information
struct TagInfo
{
	string tagName; // Tag name (e.g., "div", "a", "h1")
	set<string> classes; // Set of class names associated with the tag
	string id; // ID attribute of the tag
	string text; // Text content within the tag
	string href; // href attribute value for anchor tags
	string target; // target attribute value for anchor tags
	vector<TagInfo *> children; // Vector of child tags

	// Constructors to initialize members
	TagInfo(string name)
	{
		tagName = name;
		classes.clear();
		id = "";
		text = "";
		href = "";
		target = "";
		children.clear();
	}
	TagInfo()
	{
		tagName = "";
		classes.clear();
		id = "";
		text = "";
		children.clear();
		href = "";
		target = "";
	}
};

// Function to trim leading whitespace characters from a string
string ltrim(const string &s)
{
	size_t start = s.find_first_not_of(" \t\n\r");
	return (start == string::npos) ? "" : s.substr(start);
}

// Function to trim trailing whitespace characters from a string
string rtrim(const string &s)
{
	size_t end = s.find_last_not_of(" \t\n\r");
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

// Function to trim leading and trailing whitespace characters from a string
string trim(const string &s)
{
	return rtrim(ltrim(s));
}

// Function to extract the value of the "href" attribute from a string representing an HTML tag
string extractHREF(string &line)
{
	string href = "";

	size_t pos = 0;
	while ((pos = line.find("href=", pos)) != string::npos)
	{
		size_t start = line.find_first_of("\"'", pos + 3); // Skip "href="
		size_t end = line.find_first_of("\"'", start + 1);
		if (end != string::npos)
		{
			href = line.substr(start + 1, end - 1 - start);
			href = trim(href);
			pos = end + 1;
			return href;
		}
		else
		{
			break;
		}
	}
	return href;
}

// Function to extract the value of the "target" attribute from a string representing an HTML tag
string extractTarget(string &line)
{
	string target = "";

	size_t pos = 0;
	while ((pos = line.find("target=", pos)) != string::npos)
	{
		size_t start = line.find_first_of("\"'", pos + 3); // Skip "target="
		size_t end = line.find_first_of("\"'", start + 1);
		if (end != string::npos)
		{
			target = line.substr(start + 1, end - 1 - start);
			target = trim(target);
			pos = end + 1;
			return target;
		}
		else
		{
			break;
		}
	}
	return target;
}

// Function to extract the value of the "id" attribute from a string representing an HTML tag
string extractID(string &line)
{
	string id = "";

	size_t pos = 0;
	while ((pos = line.find("id=", pos)) != string::npos)
	{
		size_t start = line.find_first_of("\"'", pos + 3); // Skip "id="
		size_t end = line.find_first_of("\"'", start + 1);
		if (end != string::npos)
		{
			id = line.substr(start + 1, end - 1 - start);
			id = trim(id);
			pos = end + 1;
			return id;
		}
		else
		{
			break;
		}
	}
	return id;
}

// Function to extract class names from a string representing an HTML tag and return them as a set
set<string> extractClasses(const string &line)
{
	set<string> classes;
	size_t pos = 0;
	while ((pos = line.find("class=", pos)) != string::npos)
	{
		size_t start = line.find_first_of("\"'", pos + 1); // Skip "class="
		size_t end = line.find_first_of("\"'", start + 1);
		if (end != string::npos)
		{
			string classValue = line.substr(start + 1, end - start - 1);
			istringstream iss(classValue);
			string className;
			while (getline(iss, className, ' '))
			{
				classes.insert(trim(className));
			}
			pos = end + 1;
		}
		else
		{
			break;
		}
	}
	return classes;
}

// Function to extract the tag name from a string representing an HTML tag
string extractTagName(const string &line)
{
	size_t start = line.find(' ');
	return line.substr(0, start);
}

// Function to extract the text content from a string representing an HTML tag
string extractText(const string &line)
{
	size_t start = line.find('>') + 1;
	size_t end = line.find_last_of('<');
	return line.substr(start, end - start);
}

// Function to remove comments from the HTML code
string removeComments()
{
	string code = "", line;
	while (getline(cin, line))
	{
		if (line.find("<!--") == string::npos)
		{
			code += line;
			code += '\n';
			while (getline(cin, line) && line.find("<!--") == string::npos)
			{
				code += line;
				code += '\n';
			}
			if (line.find("<!--") != string::npos)
			{
				code += line.substr(0, line.find("<!--"));
				code += '\n';
				line = line.substr(line.find("<!--") + 2);
				if (line.find("-->") == string::npos)
				{
					while (getline(cin, line) && line.find("-->") == string::npos)
					{
					}
					line = line.substr(line.find("-->") + 3);
					code += line;
					code += '\n';
				}
			}
		}
	}
	return code;
}

// Function to parse the HTML code and build the tag tree
void extractCode(TagInfo *root, string prev = "")
{
	TagInfo *currentTag = root;
	string line;
	string text = "";
	if (prev != "")
	{
		if (prev.find('<') != string::npos)
		{
			int start = prev.find('<');
			text += prev.substr(0, start);
			string temp = prev.substr(start + 1);
			if (temp.find('>') == string::npos)
			{
				while (getline(CODE, line) && line.find('>') == string::npos)
				{
					temp += line;
				}
			}
			int end = temp.find('>');
			string newtag = temp.substr(0, end);
			if (newtag[0] == '/')
			{
				currentTag->text += text;
				return;
			}

			TagInfo *newTagInfo = new TagInfo();

			string tagName = extractTagName(newtag);
			string id = extractID(newtag);
			set<string> classes = extractClasses(newtag);
			string href = extractHREF(newtag);
			string target = extractTarget(newtag);
			newTagInfo->href = href;
			newTagInfo->target = target;

			newTagInfo->tagName = tagName;
			newTagInfo->id = id;
			newTagInfo->classes = classes;

			currentTag->children.push_back(newTagInfo);
			extractCode(newTagInfo, trim(temp.substr(end + 1)));
		}
		else
		{
			text += prev;
		}
	}
	while (getline(CODE, line))
	{
		if (line.find('<') == string::npos)
		{
			text += line;
			while (getline(CODE, line) && line.find('<') == string::npos)
			{
				text += line;
			}
		}
		int start = line.find('<');
		text += line.substr(0, start);
		string temp = line.substr(start + 1);
		if (temp.find('>') == string::npos)
		{
			while (getline(CODE, line) && line.find('>') == string::npos)
			{
				temp += line;
			}
			temp += line;
		}
		int end = temp.find('>');
		string newtag = temp.substr(0, end);
		if (newtag[0] == '/')
		{
			currentTag->text += text;
			return;
		}

		TagInfo *newTagInfo = new TagInfo();

		string tagName = extractTagName(newtag);
		string id = extractID(newtag);
		set<string> classes = extractClasses(newtag);
		string href = extractHREF(newtag);
		string target = extractTarget(newtag);
		newTagInfo->href = href;
		newTagInfo->target = target;

		newTagInfo->tagName = tagName;
		newTagInfo->id = id;
		newTagInfo->classes = classes;

		currentTag->children.push_back(newTagInfo);

		extractCode(newTagInfo, trim(temp.substr(end + 1)));
	}

	currentTag->text += text;
}

// Function to compute the Longest Prefix Suffix (LPS) array for the Knuth-Morris-Pratt (KMP) string searching algorithm
void computeLPS(const string &pattern, vector<int> &lps)
{
	int length = 0;
	lps[0] = 0;
	int i = 1;
	while (i < (int)pattern.length())
	{
		if (pattern[i] == pattern[length])
		{
			length++;
			lps[i] = length;
			i++;
		}
		else
		{
			if (length != 0)
			{
				length = lps[length - 1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

// Function to perform string searching using the Knuth-Morris-Pratt (KMP) algorithm
int KMPSearch(const string &pattern, const string &text)
{
	int patternLength = pattern.length();
	int textLength = text.length();

	vector<int> lps(patternLength);
	computeLPS(pattern, lps);

	int i = 0;
	int j = 0;
	while (i < textLength)
	{
		if (pattern[j] == text[i])
		{
			j++;
			i++;
		}
		if (j == patternLength)
		{
			return i - j;
			j = lps[j - 1];
		}
		else if (i < textLength && pattern[j] != text[i])
		{
			if (j != 0)
			{
				j = lps[j - 1];
			}
			else
			{
				i++;
			}
		}
	}
	return 0;
}

// Function to check if a given href attribute value contains specific keywords
bool checkLink(string href)
{
	return KMPSearch("github.com", href) || KMPSearch("freecodecamp.org", href);
}

// Function to recursively print information about HTML tags and perform validation checks
void validation(TagInfo *tag, int depth = 0)
{
	// Perform validation checks based on tag attributes and content
	if (tag->id == "welcome-section")
	{
		checks[0] = 1;
		welcomeSection++;
	}
	if (tag->tagName == "h1" and welcomeSection)
	{
		checks[1] = 1;
	}
	if (tag->tagName == "h1" and welcomeSection and tag->text != "")
	{
		checks[2] = 1;
	}
	if (tag->tagName == "h1" and welcomeSection and tag->text == "")
	{
		checks[2] = 0;
	}
	if (tag->id == "projects")
	{
		projectSection++;
		checks[3] = 1;
	}
	if (tag->tagName == "a" && tag->classes.count("project-tile") == 1)
	{
		checks[4] = 1;
	}
	if (tag->tagName == "a" && projectSection)
	{
		checks[5] = 1;
	}
	if (tag->id == "navbar")
	{
		checks[6] = 1;
		navBarId++;
	}
	if (tag->tagName == "a" && navBarId && tag->href != "" && tag->href[0] == '#')
	{
		checks[7] = 1;
	}
	if (tag->tagName == "a" && tag->id == "profile-link")
	{
		checks[8] = 1;
	}
	if (tag->tagName == "a" && tag->id == "profile-link" && checkLink(tag->href) && tag->target == "_blank")
	{
		checks[9] = 1;
	}
	if (tag->tagName == "style" && tag->text.find("@media") + 1 != 0)
	{
		checks[10] = 1;
	}
	if (tag->text != "" && !navBarId)
	{
		textTillNow++;
	}

	// Recursively process child tags
	for (auto child : tag->children)
	{
		validation(child, depth + 1);
	}

	// Update state variables and perform additional checks after processing child tags
	if (tag->id == "welcome-section")
	{
		welcomeSection--;
	}
	if (tag->id == "projects")
	{
		projectSection--;
	}
	if (tag->tagName != "" and tag->id == "navbar")
	{
		if (textTillNow == 0)
		{
			checks[11] = 1;
		}
		navBarId--;
	}
}

// Main function
int main()
{
	// Initialize validation checks vector
	checks.clear();
	checks.resize(12, 0);
	welcomeSection = 0;
	h1TagText = 0;
	projectSection = 0;
	projectTileClass = 0;
	navBarId = 0;
	textTillNow = 0;

	// Redirect standard input and output to file streams for testing purposes
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	// Create root TagInfo object to represent the entire HTML document
	TagInfo *root = new TagInfo("root");
	string code = removeComments();
	CODE << code;

	// Extract and process HTML code to build tag tree and perform validation checks
	extractCode(root);

	validation(root);

	// Print validation check results
	cout << (checks[0] ? "✓" : "X") << " Your portfolio contain a \"Welcome\" section with an id of welcome-section." << endl;
	cout << (checks[1] ? "✓" : "X") << " Your #welcome-section element had an h1 element." << endl;
	cout << (checks[2] ? "✓" : "X") << " Your portfolio don't have any empty h1 elements within #welcome-section element." << endl;
	cout << (checks[3] ? "✓" : "X") << " Your portfolio have a \"Projects\" section with an id of projects." << endl;
	cout << (checks[4] ? "✓" : "X") << " Your portfolio have one(or more than one) element with a class of project-tile." << endl;
	cout << (checks[5] ? "✓" : "X") << " Your #projects element contain one(or more than one) 'a' element." << endl;
	cout << (checks[6] ? "✓" : "X") << " Your portfolio have a navbar with an id of navbar." << endl;
	cout << (checks[7] ? "✓" : "X") << " Your #navbar element contain one 'a' element whose href attribute starts with #." << endl;
	cout << (checks[8] ? "✓" : "X") << " Your portfolio have an a element with an id of profile-link." << endl;
	cout << (checks[9] ? "✓" : "X") << " Your #profile-link element have a target attribute of _blank." << endl;
	cout << (checks[10] ? "✓" : "X") << " Your portfolio used one(or more than one) media query." << endl;
	cout << (checks[11] ? "✓" : "X") << " Your #navbar element is at the top of the viewport." << endl;

	return 0;
}
