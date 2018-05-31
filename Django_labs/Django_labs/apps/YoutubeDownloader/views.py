from django.shortcuts import render
from django import forms
from django.http import JsonResponse

from .models import downloader

# global View variables


class UrlInputForm(forms.Form):
    dir = forms.CharField(widget=forms.TextInput, initial="C:\\YoutubeDownloaded\\", label="Save directory")
    video_urls = forms.CharField(widget=forms.Textarea, label="Video links", required=False)
    playlist_urls = forms.CharField(widget=forms.Textarea, label="Playlists links", required=False)
    group_links = forms.CharField(widget=forms.Textarea,
                                  label="Groups links(links to profile! Like: https://www.youtube.com/user/woebyBright",
                                  required=False)


def index(request):
    form = UrlInputForm()
    return render(request, "YoutubeDownloader/index.html", {'form': form})


def downloaded_page(request):
    directory = request.POST.get('dir')
    downloader.directory = directory

    for i, item in enumerate(downloader.thread_poll) :
        item.join()

    downloader.thread_poll.clear()
    downloader.videos_info.clear()

    try:
        urls_data = request.POST.get('video_urls')
        urls = urls_data.split('\r\n')
        downloader.process_direct_links(urls)
    except:
        pass

    try:
        playlists = request.POST.get('playlist_urls')
        playlist_urls = playlists.split('\r\n')
        downloader.process_playlists(playlist_urls)
    except:
        pass

    try:
        groups = request.POST.get('group_links')
        group_links = groups.split('\r\n')
        downloader.process_profile_pages(group_links)
    except:
        pass

    downloader.logger.debug(downloader.videos_info)

    return render(request, "YoutubeDownloader/loaded_files.html", {'data': directory})


def check_loaded_state(request):
    return JsonResponse(downloader.videos_info, safe=False)