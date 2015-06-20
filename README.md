# QtTestRunner
A GUI tool for running unit tests using the Qt Test framework.

I've always avoided the Qt Test framework because it makes just about zero sense to me. You have to make some custom code to get everything to run in a single executable, and then you quickly realize that the plain-text output is 99% unmaintainable. When a test fails, you might have to scroll (or CTRL+F) to find the test that failed. For more information on why I think vanilla Qt Test is unusable, check out my unanswered Stackoverflow question:

http://stackoverflow.com/questions/30836790/how-can-the-qt-test-framework-be-used-for-real-world-projects

In my rage to get Qt Test to be somewhat usable, I decided to make this GUI tool. Not even going to bother TDDing it (because how would I do that? The tools don't exist unless you want to bring in a dependency like Google Test).