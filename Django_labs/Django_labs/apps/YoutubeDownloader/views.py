from django.shortcuts import render
from django import forms
from pytube import YouTube
from pytube import Playlist
import os
import urllib
import re
import logging

# Get an instance of a logger
logger = logging.getLogger(__name__)


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

    urls_data = request.POST.get('video_urls')
    urls = urls_data.split('\r\n')

    playlists = request.POST.get('playlist_urls')
    playlist_urls = playlists.split('\r\n')

    groups = request.POST.get('group_links')
    group_links = groups.split('\r\n')

    try:
        download_urls(urls, directory)
    except:
        pass

    try:
        for playlist in playlist_urls:
            pl = Playlist(url=playlist)
            pl_dir = directory + playlist.split("list=")[1] + "\\"

            if not os.path.exists(pl_dir):
                os.makedirs(pl_dir)

            pl.populate_video_urls()
            download_urls(pl.video_urls, pl_dir)
    except:
        pass

    try:
        for group in group_links:
            group_link_parts = group.split('/')
            if group_link_parts[len(group_link_parts)-2] != 'user':
                continue
            user = group_link_parts[len(group_link_parts)-1]
            group_dir = directory + user
            group += '/videos'
            html_content = urllib.request.urlopen(group)
            video_codes = re.findall(r'href=\"\/watch\?v=(.{11})', html_content.read().decode())
            video_codes = set(video_codes)
            group_videos = []
            for code in video_codes:
                group_videos.append("https://www.youtube.com/watch?v=" + code)
            download_urls(group_videos, group_dir)
    except:
        pass

    return render(request, "YoutubeDownloader/loaded_files.html", {'data': directory})


def download_urls(urls, directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

    video_infos = []
    for url in urls:
        video_infos.append(get_video_info_data(url))
        yt = YouTube(url=url)
        yt.streams \
            .filter(progressive=True, file_extension='mp4') \
            .order_by('resolution') \
            .desc() \
            .first() \
            .download(directory)


def get_video_info_data(url):
    info_data = {}

