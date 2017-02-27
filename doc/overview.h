/**

\mainpage Monkey web page <a href="https://github.com/rete/Monkey">https://github.com/rete/Monkey</a>

<b>Monkey</b>
is a unified c++ interface for markup languages and others.

<h2>Overview</h2>

The main purpose of Monkey is to provide a unified interface to different markup languages and others. For example, you can parse a XML file with Monkey, edit its contents as needed and re-export it in JSON or other supported languages.
It means that an application that uses Monkey to parse a configuration file will makes no assumption on the file format.
C++ objects provided by Monkey are very similar to the yaml-cpp interface. However, additional functionalities are provided to support XML elements attributes in other languages.
The central class in Monkey is monkey::Node. It corresponds i.e to :
<ul>
  <li> a XML element </li>
  <li> a YAML node </li>
  <li> a JSON value </li>
  <li> a row into a MySQL table (see MySQL support) </li>
</ul>

The currently supported format are the following :

<ul>
  <li>XML</li>
  <li>Json</li>
  <li>Yaml</li>
  <li>MySQL : Monkey provides a MySQL support to read/write your monkey::Node into a MySQL table, allowing to, i.e, centralize your configuration into a database. Since Monkey provides different format conversions, you can also pull your monkey::Node from a MySQL database into a local file (among the Monkey supported formats), edit your file locally and push it again into your MySQL database</li>
  <li>Binary : Monkey defines its own binary format to read/write your monkey::Node into a file or in a buffer</li>
</ul>


<h2>Installation</h2>

The Monkey sources are available at : <a href="https://github.com/rete/Monkey">https://github.com/rete/Monkey</a>

One can download the source using the clone git command :

\code{.sh}
git clone https://github.com/rete/Monkey.git
\endcode

One can choose the Monkey version :

\code{.sh}
git tag # list available versions
git checkout "your-version"
\endcode

Monkey versions scheme follows the convention vMajor-Minor-Patch, i.e v01-02-14.

To install the package :

\code{.sh}
mkdir build
cd build
cmake [-DOPTIONS=ON/OFF] ..
make install
\endcode

Available options are :

<ul>
  <li>INSTALL_DOC (ON/OFF) : to generate and install Doxygen code documentation. Default is OFF</li>
  <li>${FORMAT}_SUPPORT (ON/OFF) : to compile the support for the <i>FORMAT</i>. For example, for the Json support, use the Json_SUPPORT cmake option. By default, all format support cmake options are set to OFF.</li>
</ul>

For example, to generate Doxygen doc and build the Xml and Json suports :

\code{.sh}
cmake -DINSTALL_DOC=ON -DJson_SUPPORT=ON -DXml_SUPPORT=ON ..
\endcode

<h2>Format converters</h2>

To jump from one format to another (like a monkey is jumping from a tree to another ...), one can use the binaries provided my Monkey. If you built the package with at least two formats (i.e Xml and Json), you may found the bianries into the <i>bin</i> directory.
Binary names have to following syntax : monkey-<i>format1</i>-to-<i>format2</i> with <i>format1</i> and <i>format2</i> the desired formats in lower case. To convert a Json file to a Xml file, one can use :

\code{.sh}
monkey-json-to-xml myJsonInputFile.json myXmlOutputFile.xml
\endcode

For the Monkey MySQL push/pull process, see MySQL support.

<h2>Reading and writing files</h2>

To parse a file in a specific format, one can use the parser classes. The following code parses a Xml file using the monkey::XmlParser and gets the xml structure in a monkey::Node :

\code
monkey::XmlParser xmlParser;
monkey::Node rootNode;
xmlParser.readFile("myXmlFile.xml", rootNode);
// ... work with monkey::Node ...
\endcode

Users can work with the root node and write it in a new file using the same parser classes. The following code write the previous root monkey::Node in a Json file :

\code
monkey::JsonParser jsonParser;
jsonParser.writeFile("myJsonFile.json", rootNode);
\endcode

<h2>Node edition</h2>

The monkey::Node class is the main interface for editing contents. Nodes can handle different type of data structure : scalar values, sequence, map or can be null.

\code
// node with type 'Null'
monkey::Node node;

// transform this node into a scalar value of type double
node = 5.2;

// node type is dynamic., i.e changing from scalar to sequence type
node.push_back(4.5);
node.push_back("A string");

// node can be also be a map.
// let change it to a map by adding key/value pairs
node.insert("address", "14 Baker street");
node.insert("the answer", 42);

std::vector<unsigned int> myList = {45, 78, 4511};
node.insert("list", myList);
\endcode

The following piece of code parses the previous node in its map state :

\code
std::string myAddress = node["address"].as<std::string>();

// numbers can be converted in multiple formats
double answerDouble = node["the answer"].as<double>(); // 42.0
unsigned int answerUInt = node["the answer"].as<unsigned int>(); // 42
std::string answerString = node["the answer"].as<std::string>(); // "42"

// access lists in the same maner
std::vector<double> listDouble = node["list"].as<std::vector<double>>(); // {45.0, 78.0, 4511.0}
std::vector<unsigned int> listUint = node["list"].as<std::vector<unsigned int>>(); // {45, 78, 4511}
std::vector<std::string> listString = node["list"].as<std::vector<std::string>>(); // {"45", "78", "4511"}
\endcode

For nodes with map type, one can iterate on the different key value pairs :

\code
for(monkey::Node::iterator iter = node.begin() ; iter != node.end() ; ++iter)
  std::cout << "-> " << iter->first << " : " << iter->second.as<std::string>() << std::endl;
\endcode

You can also perform operation depending on node type :

\code
Node::Type type = node.type();

switch(type)
{
  case monkey::Node::Null: // do something ...
  case monkey::Node::Scalar: // do something ...
  case monkey::Node::Sequence: // do something ...
  case monkey::Node::Map: // do something ...
}
\endcode

Nodes can be nested :

\code

monkey::Node frodonInfo(monkey::Node::Map);
userInfo.insert("user", "Frodon");
userInfo.insert("password", "InLoveWithSam");
userInfo.insert("email", "frodon.sacquet@gmail.com");

monkey::Node obiwanInfo(monkey::Node::Map);
userInfo.insert("user", "obi-ken");
userInfo.insert("password", "QuiGonMaster");
userInfo.insert("email", "obiwan.kenobi@gmail.com");

monkey::Node users(monkey::Node::Sequence);
users.push_back(frodonInfo);
users.push_back(obiwanInfo);

monkey::Node rootNode(monkey::Node::Map);
rootNode.inser("users", users);
\endcode

See monkey::Node class documentation for additional methods

<h2>Support</h2>

If you have any questions or proposals for new features please contact the author :
<a href="mailto:Ete Remi&lt;remi.ete@gmail.com&gt;">remi.ete@gmail.com</a>. <br/>
To report bugs, issues or to perform a pull request, use the <a href="https://github.com/rete/Monkey/issues">github interface</a>.





<!-->
<h2>Running Marlin</h2>
After having installed Marlin you have to write your own marlin::Processor(s) subclass
that performs the computation. This is fairly straight forward and Marlin provides
an example in "$MARLIN/examples/mymarlin" that can serve as a template for your own
projects.
<p>
Note: there is no need to write a main program as this is provided by Marlin. Existing
Processors are automatically registered with Marlin provided one instance exists in the
library as described in the <a href="../README">README</a>.


<h3>Steering files</h3>
A Marlin application is controlled via a steering file that defines the active processors
and the order in which they are called as well as global and processor specific
parameters. The default format of the steering files is xml (older ascci steering files are still supported
for a transition period)


<h4>XML steering files</h4>

You can get an example XML steering file with:
<ul>
<li>
  <b>./bin/Marlin -x > example.xml</b>
</li>
</ul>
The XML steering files provide the following features:
<ul>
<li> definition of the program flow (order of processors to be executed)</li>
<li> global parameters</li>
<li> processor parameters</li>
<li> conditional execution of processors (depending on flags set by other processors)</li>
<li> grouping of processors sharing common parameters</li>
</ul>

See marlin::XMLParser for a detailed description of the xml steering files.

The application is run by:
<ul>
<li>
  <b>./bin/Marlin example.xml</b>
</li>
</ul>

<h4>Old Ascii steering files</h4>

You can convert old ascii steering files to xml steering files by typing:
<ul>
<li>
  <b>./bin/Marlin -o old.steer new.xml </b>
</li>
</ul>

<h4> Other commands </h4>
You can get a list of all supported command line options with
<ul>
<li>
  <b>./bin/Marlin -h </b>
</li>
</ul>
This will create the following output:
<pre>
 Usage: Marlin [OPTION] [FILE]...
   runs a Marlin application

 Running the application with a given steering file:
   Marlin steer.xml

   Marlin -h                     print this help information
   Marlin -?                     print this help information
   Marlin -x                     print an example steering file to stdout
   Marlin -c steer.xml           check the given steering file for consistency
   Marlin -f old.xml new.xml     convert old xml files to new xml files for consistency check
   Marlin -o old.steer new.xml   convert old steering file to xml steering file
   Marlin -l                     [deprecated: old format steering file example]
   Marlin -d steer.xml flow.dot  create a program flow diagram (see: http://www.graphviz.org)

 Example:
 To create a new default steering file from any Marlin application, run
     Marlin -x > mysteer.xml
 and then use either an editor or the MarlinGUI to modify the created steering file
 to configure your application and then run it. e.g. :
     Marlin mysteer.xml > marlin.out 2>&1 &

</pre>

<h3>Release Notes</h3>
Marlin is under development and there are frequent releases. Please check the
<a href="../release.notes">./release.notes</a>

<hr>
<p>
If you have any questions or proposals for new features please contact the author:

<a href="mailto:Frank Gaede &lt;frank.gaede@desy.de&gt;">frank.gaede@desy.de</a> <!-->
*/

/* namespace monkey */
namespace monkey {}
