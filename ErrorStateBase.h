#pragma once

class ErrorStateBase
{
public:

	enum ErrorCode {
		SUCCESS,
		VIDEO_INITIALIZATION_FAILED,
		VIDEO_MODE_SET_FAILED,
		VIDEO_QUERY_FAILED,
		GLEW_INIT_FAILED,
		INVALID_SURFACE_AFTER_RESIZE,
		SHADER_COMPILATION_ERROR,
		SHADER_FILE_NOT_FOUND
	};

	ErrorStateBase();
	virtual ~ErrorStateBase();

	bool checkState() const;

protected:

	ErrorCode errorState;
};
