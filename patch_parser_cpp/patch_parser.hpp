#pragma once

#include <sstream>
#include <string>
#include <vector>

/*========================================================================
FileDelta Class: Contains data about specific file changes in the patch
========================================================================*/
class FileDelta {
public:

	FileDelta():
		OriginalFileName(),
		NewFileName(),
		RemovedLines(),
		AddedLines(),
		LinesRemovedCount(0),
		LinesAddedCount(0)
	{}

	bool Parse(std::stringstream& ss, std::string& fileNames)
	{
		std::string line;

		while(getline(ss, line) && line.rfind("--- ", 0) != 0)
			continue;

		if(line.rfind("--- ", 0) == 0)
			ParseOriginalName(line);
		else 
			return false;


		while(getline(ss, line) && line.rfind("+++ ", 0) != 0)
			continue;

		if(line.rfind("+++ ", 0) == 0)
			ParseNewName(line);
		else
			return false;


		while(getline(ss, line))
		{
			if(line.rfind("--", 0) == 0 && line.length() == 2)
				break;

			if(line.rfind("+", 0) == 0)
			{
				AddedLines.push_back(line);
				LinesAddedCount++;
			}
			else if(line.rfind("-", 0) == 0)
			{
				RemovedLines.push_back(line);
				LinesRemovedCount++;
			}
		}
	}

	int GetLinesRemoved() const
	{
		return LinesRemovedCount;
	}

	int GetLinesAdded() const
	{
		return LinesAddedCount;
	}

	std::string GetOriginalFileName() const
	{
		return OriginalFileName;
	}

	std::string GetNewFileName() const
	{
		return NewFileName;
	}

private:

	void ParseOriginalName(std::string rawOriginalFile)
	{
		std::stringstream ss(rawOriginalFile);
		std::string line;

		if(!getline(ss, line, ' ') || line.rfind("---", 0) != 0)
			return;

		if(getline(ss, line, ' '))
			OriginalFileName = line;
	}

	void ParseNewName(std::string rawNewFile)
	{
		std::stringstream ss(rawNewFile);
		std::string line;

		if(!getline(ss, line, ' ') || line.rfind("+++", 0) != 0)
			return;

		if(getline(ss, line, ' '))
			NewFileName = line;
	}

private:
	std::string OriginalFileName;
	std::string NewFileName;

	std::vector<std::string> RemovedLines;
	std::vector<std::string> AddedLines;

	int LinesRemovedCount = 0;
	int LinesAddedCount = 0;
};


/*========================================================================
FileDelta Class: Contains data about the entire patch file
========================================================================*/
class Patch {
public:

	const std::string DIFF_KEY = "diff --git";

	Patch(): 
		RawPatch(),
		FileDeltas(),
		FileChangeCount(0),
		LinesRemovedCount(0),
		LinesAddedCount(0)
	{
	}

	Patch(std::string patch): 
		RawPatch(patch),
		FileDeltas(),
		FileChangeCount(0),
		LinesRemovedCount(0),
		LinesAddedCount(0)
	{
	}

	void SetPatch(std::string patch)
	{
		RawPatch = patch;
	}

	bool Parse()
	{
		if(!RawPatch.length()) 
			return false;

		std::stringstream ss(RawPatch);
		std::string line;

		while(getline(ss, line))
		{
			if(line.rfind(DIFF_KEY, 0) == 0)
			{
				FileDelta fileChange;
				
				if(fileChange.Parse(ss, line))
				{
					FileDeltas.push_back(fileChange);
					LinesRemovedCount += fileChange.GetLinesRemoved();
					LinesAddedCount += fileChange.GetLinesAdded();
				}

			}
		}

		
		return true;
	}


	void SetAuthorName(std::string& author)
	{
		Author = author;
	}

	std::string GetAuthorName() const
	{
		return Author;
	}

	int GetLinesAdded() const
	{
		return LinesAddedCount;
	}

	int GetLinesRemoved() const
	{
		return LinesRemovedCount;
	}

	std::vector<FileDelta> GetFileDeltas() const
	{
		return FileDeltas;
	}

private:
	std::string RawPatch;
	std::string Author;

	std::vector<FileDelta> FileDeltas;

	int FileChangeCount;
	int LinesRemovedCount;
	int LinesAddedCount;
};