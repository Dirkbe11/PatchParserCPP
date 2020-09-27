#include <iostream>
#include <fstream>
#include <string>

#include <PatchParserCPP/PatchParser.hpp>
#include "gtest/gtest.h"

namespace
{
	constexpr char ONE_FILE_ONE_CHUNK_PATCH_NAME[] = "../UnitTest/TestPatches/OneFileOneChunkPatch.txt";
	constexpr int ONE_FILE_DELTA = 1;
	constexpr int ONE_FILE_ONE_CHUNK_PATCH_ADDED_LINES = 54;
	constexpr int ONE_FILE_ONE_CHUNK_PATCH_REMOVED_LINES = 2;
	constexpr char ONE_FILE_ONE_CHUNK_PATCH_ORIGINAL_FILE[] = "/dev/null";
	constexpr char ONE_FILE_ONE_CHUNK_PATCH_NEW_FILE[] = "b/tools/testing/selftests/bpf/prog_tests/snprintf_btf.c";

	constexpr char ONE_FILE_TWO_CHUNKS_PATCH_NAME[] = "../UnitTest/TestPatches/OneFileTwoChunksPatch.txt";
	constexpr int ONE_FILE_TWO_CHUNKS_PATCH_ADDED_LINES = 2;
	constexpr int ONE_FILE_TWO_CHUNKS_PATCH_REMOVED_LINES = 2;
	constexpr char ONE_FILE_TWO_CHUNK_PATCH_ORIGINAL_FILE[] = "a/drivers/hid/hid-input.c";
	constexpr char ONE_FILE_TWO_CHUNK_PATCH_NEW_FILE[] = "b/drivers/hid/hid-input.c";

	constexpr char TWO_FILE_TWO_CHUNK_PATCH_NAME[] = "../UnitTest/TestPatches/TwoFileTwoChunkPatch.txt";
	constexpr int TWO_FILE_DELTA = 2;
	constexpr int TWO_FILE_TWO_CHUNKS_PATCH_ADDED_LINES = 4;
	constexpr int TWO_FILE_TWO_CHUNKS_PATCH_REMOVED_LINES = 4;
	constexpr int TWO_FILE_TWO_CHUNKS_PATCH_FILE_ADDED_LINES = 2;
	constexpr int TWO_FILE_TWO_CHUNKS_PATCH_FILE_REMOVED_LINES = 2;
	constexpr char TWO_FILE_TWO_CHUNK_PATCH_FIRST_ORIGINAL_FILE[] = "a/drivers/hid/hid-input1.c";
	constexpr char TWO_FILE_TWO_CHUNK_PATCH_FIRST_NEW_FILE[] = "b/drivers/hid/hid-input1.c";
	constexpr char TWO_FILE_TWO_CHUNK_PATCH_SECOND_ORIGINAL_FILE[] = "a/drivers/hid/hid-input2.c";
	constexpr char TWO_FILE_TWO_CHUNK_PATCH_SECOND_NEW_FILE[] = "b/drivers/hid/hid-input2.c";
}

TEST(OneFileOneChunkPatch, GivenPatchWithOneFileChangeAndOneChunkThenTheLineEditCountsAreCorrect)
{
	std::ifstream patchFile(ONE_FILE_ONE_CHUNK_PATCH_NAME);
	std::string rawPatch((std::istreambuf_iterator<char>(patchFile)),
					     (std::istreambuf_iterator<char>()));

    Patch patch(rawPatch);
    patch.Parse();

    int addedLines = patch.GetLinesAdded();
    int removedLines = patch.GetLinesRemoved();
    std::vector<FileDelta> fileDeltas = patch.GetFileDeltas();

    EXPECT_EQ(addedLines, ONE_FILE_ONE_CHUNK_PATCH_ADDED_LINES);
    EXPECT_EQ(removedLines, ONE_FILE_ONE_CHUNK_PATCH_REMOVED_LINES);

    ASSERT_EQ(fileDeltas.size(), ONE_FILE_DELTA);

    FileDelta fileDelta = fileDeltas[0];
    EXPECT_EQ(fileDelta.GetLinesAdded(), ONE_FILE_ONE_CHUNK_PATCH_ADDED_LINES);
    EXPECT_EQ(fileDelta.GetLinesRemoved(), ONE_FILE_ONE_CHUNK_PATCH_REMOVED_LINES);
    EXPECT_EQ(fileDelta.GetOriginalFileName(), ONE_FILE_ONE_CHUNK_PATCH_ORIGINAL_FILE);
    EXPECT_EQ(fileDelta.GetNewFileName(), ONE_FILE_ONE_CHUNK_PATCH_NEW_FILE);
}

TEST(OneFileTwoChunks, GivenPatchWithOneFileAndOneChunkThenThePatchIsParsedCorrectly)
{
	std::ifstream patchFile(ONE_FILE_TWO_CHUNKS_PATCH_NAME);
	std::string rawPatch((std::istreambuf_iterator<char>(patchFile)),
					     (std::istreambuf_iterator<char>()));

    Patch patch(rawPatch);
    patch.Parse();

    int addedLines = patch.GetLinesAdded();
    int removedLines = patch.GetLinesRemoved();
    std::vector<FileDelta> fileDeltas = patch.GetFileDeltas();

    EXPECT_EQ(addedLines, ONE_FILE_TWO_CHUNKS_PATCH_ADDED_LINES);
    EXPECT_EQ(removedLines, ONE_FILE_TWO_CHUNKS_PATCH_REMOVED_LINES);

    ASSERT_EQ(fileDeltas.size(), ONE_FILE_DELTA);

    FileDelta fileDelta = fileDeltas[0];
    EXPECT_EQ(fileDelta.GetLinesAdded(), ONE_FILE_TWO_CHUNKS_PATCH_ADDED_LINES);
    EXPECT_EQ(fileDelta.GetLinesRemoved(), ONE_FILE_TWO_CHUNKS_PATCH_REMOVED_LINES);
    EXPECT_EQ(fileDelta.GetOriginalFileName(), ONE_FILE_TWO_CHUNK_PATCH_ORIGINAL_FILE);
    EXPECT_EQ(fileDelta.GetNewFileName(), ONE_FILE_TWO_CHUNK_PATCH_NEW_FILE);
}

TEST(TwoFileTwoChunks, GivenPatchWithTwoFilesAndOneChunkThenThePatchIsParsedCorrectly)
{
	std::ifstream patchFile(TWO_FILE_TWO_CHUNK_PATCH_NAME);
	std::string rawPatch((std::istreambuf_iterator<char>(patchFile)),
					     (std::istreambuf_iterator<char>()));

    Patch patch(rawPatch);
    patch.Parse();

    int addedLines = patch.GetLinesAdded();
    int removedLines = patch.GetLinesRemoved();
    std::vector<FileDelta> fileDeltas = patch.GetFileDeltas();

    EXPECT_EQ(addedLines, TWO_FILE_TWO_CHUNKS_PATCH_ADDED_LINES);
    EXPECT_EQ(removedLines, TWO_FILE_TWO_CHUNKS_PATCH_REMOVED_LINES);

    ASSERT_EQ(fileDeltas.size(), TWO_FILE_DELTA);

    FileDelta fileDelta = fileDeltas[0];
    EXPECT_EQ(fileDelta.GetLinesAdded(), TWO_FILE_TWO_CHUNKS_PATCH_FILE_ADDED_LINES);
    EXPECT_EQ(fileDelta.GetLinesRemoved(), TWO_FILE_TWO_CHUNKS_PATCH_FILE_REMOVED_LINES);
    EXPECT_EQ(fileDelta.GetOriginalFileName(), TWO_FILE_TWO_CHUNK_PATCH_FIRST_ORIGINAL_FILE);
    EXPECT_EQ(fileDelta.GetNewFileName(), TWO_FILE_TWO_CHUNK_PATCH_FIRST_NEW_FILE);

    fileDelta = fileDeltas[1];
    EXPECT_EQ(fileDelta.GetLinesAdded(), TWO_FILE_TWO_CHUNKS_PATCH_FILE_ADDED_LINES);
    EXPECT_EQ(fileDelta.GetLinesRemoved(), TWO_FILE_TWO_CHUNKS_PATCH_FILE_REMOVED_LINES);
    EXPECT_EQ(fileDelta.GetOriginalFileName(), TWO_FILE_TWO_CHUNK_PATCH_SECOND_ORIGINAL_FILE);
    EXPECT_EQ(fileDelta.GetNewFileName(), TWO_FILE_TWO_CHUNK_PATCH_SECOND_NEW_FILE);
}