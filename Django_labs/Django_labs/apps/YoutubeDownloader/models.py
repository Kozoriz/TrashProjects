from django.db import models

import os
import urllib
import re
import logging
import time
import threading

import pytube

logging.basicConfig(
            level=logging.DEBUG,
            format='%(asctime)s %(levelname)s %(message)s',
        )
logger = logging.getLogger(__name__)


class YoutubeDownloader:
    def __init__(self, save_dir="C:\\YoutubeDownloaded\\"):
        self.directory = save_dir

        self.logger = logging.getLogger(__name__)
        self.logger.debug("Class %s initializated", __name__)

        self.videos_info = []
        self.thread_poll = []

    def process_direct_links(self, links):
        try:
            self.download_urls(links, self.directory)
        except:
            self.logger.error("Error occurred during Direct links downloading")

    def process_playlists(self, playlist_links):
        try:
            for playlist in playlist_links:
                pl = pytube.Playlist(url=playlist)
                pl_dir = self.directory + playlist.split("list=")[1] + "\\"

                if not os.path.exists(pl_dir):
                    os.makedirs(pl_dir)

                pl.populate_video_urls()
                self.download_urls(pl.video_urls, pl_dir)
        except:
            self.logger.error("Error occurred during Playlist links processing")

    def process_profile_pages(self, profile_links):
        try:
            for group in profile_links:
                group_link_parts = group.split('/')
                if group_link_parts[len(group_link_parts) - 2] != 'user':
                    continue
                user = group_link_parts[len(group_link_parts) - 1]
                group_dir = self.directory + user
                group += '/videos'
                html_content = urllib.request.urlopen(group)
                video_codes = re.findall(r'href=\"\/watch\?v=(.{11})', html_content.read().decode())
                video_codes = set(video_codes)
                group_videos = []
                for code in video_codes:
                    group_videos.append("https://www.youtube.com/watch?v=" + code)
                self.download_urls(group_videos, group_dir)
        except:
            self.logger.error("Error occurred during Group links processing")

    def thread_worker(self, url, directory, current_url_info, callback):
        self.logger.debug("thread url %s", url)
        yt = pytube.YouTube(url=url, on_progress_callback=callback)
        try:
            yt.streams \
                .filter(progressive=True, file_extension='mp4') \
                .order_by('resolution') \
                .desc() \
                .first() \
                .download(directory, filename=current_url_info['name'])
            pass
        except:
            self.logger.error("Error occurred during downloading : %s", url)

    def download_urls(self, urls, directory):
        if not os.path.exists(directory):
            os.makedirs(directory)

        for url in urls:
            current_url_info = {}
            try:
                current_url_info =  self.get_video_info_data(url)
                current_url_info['name'] = pytube.helpers.safe_filename(current_url_info['name'])
                self.videos_info.append(current_url_info)
            except:
                self.logger.debug("Error getting video info")

            try:
                thread = threading.Thread(name=url, target=self.thread_worker, args=(url, directory, current_url_info, some_callback ))
                thread.start()
                self.thread_poll.append(thread)
                logger.debug(self.thread_poll)
            except:
                logger.exception("exception")

    def get_video_info_data(self, url):
        info_data = {}
        html_content = urllib.request.urlopen(url).read().decode()

        info_data['url'] = url
        try:
            info_data['name'] = re.findall("<title>(.*)</title>", html_content)[0]
        except:
            self.logger.error("Video title not found. Page url : %s", url)
        return info_data


downloader = YoutubeDownloader("")

def some_callback(stream, chunk, file_handler, bytes_remaining):
    try:
        filename=re.findall("\\\(.*)\\\(.*)(\\.\\w*)",file_handler.name)
        index = [i for i, item in enumerate(downloader.videos_info) if item['name']==filename[0][1]]
        downloader.videos_info[index[0]]['bytes_remaining'] = bytes_remaining

        # logger.debug("%s", downloader.videos_info[index[0]])
    except:
        logger.exception("something went wrong")

