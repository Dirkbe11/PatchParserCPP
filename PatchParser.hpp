#pragma once

#include <string>
#include <vector>



/*========================================================================
FileDelta Class: Contains data about specific file changes in the patch
========================================================================*/
class FileDelta {
public:
	FileDelta(std::string FileDiff):
		RawFileDiff(FileDiff)
	{}



private:
	std::string RawFileDiff;

	std::string OriginalFileName;
	std::string NewFilename;

	std::vector<std::string> RemovedLines;
	std::vector<std::string> AddedLines;

	int LinesRemovedCount = 0;
	int LinesAddedCount = 0;
}

/*========================================================================
FileDelta Class: Contains data about the entire patch file
========================================================================*/
class Patch {
public:

	Patch(std::string patch): 
		RawPatch(patch),
		FileDelta()
		FileChangeCount(0),
		LinesAddedCount(0),
		LinesRemovedCount(0)
	{}

	void SetPatch(std::string patch)
	{
		RawPatch = patch;
	}

	bool Parse()
	{
		if(!RawPatch.length()) 
			return false;

		size_t startIndex = StripMetaData();
		

		return false;
	}

private:

	size_t StripMetaData()
	{
		size_t FirstFileChange = RawPatch.find("diff --git");

		return FirstFileChange;
	}

private:
	std::string RawPatch;
	std::vector<FileDelta> FileDeltas;

	int FileChangeCount;
	int LinesAddedCount;
	int LinesRemovedCount;
}




